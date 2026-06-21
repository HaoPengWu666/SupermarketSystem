DROP DATABASE IF EXISTS 超市销售管理系统;

CREATE DATABASE IF NOT EXISTS 超市销售管理系统;
USE 超市销售管理系统;

-- 1. 员工表
CREATE TABLE 员工表 (
    员工ID INT PRIMARY KEY AUTO_INCREMENT,
    姓名 VARCHAR(20) NOT NULL,
    性别 ENUM('男','女') NOT NULL,
    电话 VARCHAR(20),
    角色 ENUM('收银员','库存管理员','经理') NOT NULL,
    用户名 VARCHAR(20) NOT NULL UNIQUE,
    密码 VARCHAR(32) NOT NULL
);

-- 2. 供应商表
CREATE TABLE 供应商表 (
    供应商ID INT PRIMARY KEY AUTO_INCREMENT,
    名称 VARCHAR(50) NOT NULL,
    联系人 VARCHAR(20),
    联系电话 VARCHAR(20)
);

-- 3. 会员表
CREATE TABLE 会员表 (
    会员ID INT PRIMARY KEY AUTO_INCREMENT,
    姓名 VARCHAR(20) NOT NULL,
    电话 VARCHAR(20) NOT NULL,
    积分 INT DEFAULT 0,
    消费总额 DECIMAL(10,2) DEFAULT 0,
    折扣率 DECIMAL(3,2) DEFAULT 1.0 CHECK (折扣率 BETWEEN 0.5 AND 1.0),
    注册日期 DATE NOT NULL
);

-- 4. 商品表
CREATE TABLE 商品表 (
    商品条码 VARCHAR(20) PRIMARY KEY,
    商品名称 VARCHAR(100) NOT NULL,
    规格 VARCHAR(20),
    零售价 DECIMAL(10,2) NOT NULL,
    成本价 DECIMAL(10,2) NOT NULL,
    库存数量 INT NOT NULL DEFAULT 0,
    供应商ID INT,
    FOREIGN KEY (供应商ID) REFERENCES 供应商表(供应商ID)
);

-- 5. 销售单表
CREATE TABLE 销售单表 (
    销售单号 INT PRIMARY KEY AUTO_INCREMENT,
    销售日期 DATETIME NOT NULL,
    员工ID INT NOT NULL,
    会员ID INT,
    总金额 DECIMAL(10,2) NOT NULL,
    支付方式 ENUM('现金','会员卡','微信','支付宝') NOT NULL,
    FOREIGN KEY (员工ID) REFERENCES 员工表(员工ID),
    FOREIGN KEY (会员ID) REFERENCES 会员表(会员ID)
);

-- 6. 销售明细表
CREATE TABLE 销售明细表 (
    明细ID INT PRIMARY KEY AUTO_INCREMENT,
    销售单号 INT NOT NULL,
    商品条码 VARCHAR(20) NOT NULL,
    销售数量 INT NOT NULL,
    售价 DECIMAL(10,2) NOT NULL,
    折扣率 DECIMAL(3,2) DEFAULT 1.0,
    FOREIGN KEY (销售单号) REFERENCES 销售单表(销售单号),
    FOREIGN KEY (商品条码) REFERENCES 商品表(商品条码)
);

-- 7. 进货单表
CREATE TABLE 进货单表 (
    进货单号 INT PRIMARY KEY AUTO_INCREMENT,
    进货日期 DATETIME NOT NULL,
    员工ID INT NOT NULL,
    供应商ID INT NOT NULL,
    总金额 DECIMAL(10,2) NOT NULL,
    FOREIGN KEY (员工ID) REFERENCES 员工表(员工ID),
    FOREIGN KEY (供应商ID) REFERENCES 供应商表(供应商ID)
);

-- 8. 进货明细表
CREATE TABLE 进货明细表 (
    明细ID INT PRIMARY KEY AUTO_INCREMENT,
    进货单号 INT NOT NULL,
    商品条码 VARCHAR(20) NOT NULL,
    进货数量 INT NOT NULL,
    进价 DECIMAL(10,2) NOT NULL,
    FOREIGN KEY (进货单号) REFERENCES 进货单表(进货单号),
    FOREIGN KEY (商品条码) REFERENCES 商品表(商品条码)
);



-- 视图设计
-- 1. 销售汇总视图
CREATE VIEW 销售汇总视图 AS
SELECT 
    s.销售单号,
    s.销售日期,
    e.姓名 AS 收银员,
    IFNULL(m.姓名, '非会员') AS 顾客,
    s.总金额,
    s.支付方式,
    COUNT(d.明细ID) AS 商品种类数
FROM 销售单表 s
JOIN 员工表 e ON s.员工ID = e.员工ID
LEFT JOIN 会员表 m ON s.会员ID = m.会员ID
JOIN 销售明细表 d ON s.销售单号 = d.销售单号
GROUP BY s.销售单号, s.销售日期, e.姓名, m.姓名, s.总金额, s.支付方式;

-- 2. 商品库存视图
CREATE VIEW 商品库存视图 AS
SELECT 
    p.商品条码,
    p.商品名称,
    p.规格,
    p.零售价,
    p.库存数量,
    v.名称 AS 供应商,
    CASE 
        WHEN p.库存数量 <= 10 THEN '需补货'
        WHEN p.库存数量 <= 20 THEN '库存紧张'
        ELSE '库存充足'
    END AS 库存状态
FROM 商品表 p
LEFT JOIN 供应商表 v ON p.供应商ID = v.供应商ID;

-- 3. 会员消费视图
CREATE VIEW 会员消费视图 AS
SELECT 
    m.会员ID,
    m.姓名,
    m.电话,
    m.积分,
    m.消费总额,
    COUNT(DISTINCT s.销售单号) AS 消费次数,
    MAX(s.销售日期) AS 最近消费日期
FROM 会员表 m
LEFT JOIN 销售单表 s ON m.会员ID = s.会员ID
GROUP BY m.会员ID, m.姓名, m.电话, m.积分, m.消费总额;

-- 4.创建库存预警视图
CREATE VIEW 库存预警视图 AS
SELECT 
    商品条码,
    商品名称,
    规格,
    零售价,
    库存数量,
    CASE 
        WHEN 库存数量 <= 10 THEN '红色预警'
        WHEN 库存数量 <= 20 THEN '黄色预警'
        ELSE '正常'
    END AS 预警级别,
    CASE 
        WHEN 库存数量 <= 10 THEN '需立即补货'
        WHEN 库存数量 <= 20 THEN '建议补货'
        ELSE '库存充足'
    END AS 建议措施
FROM 商品表
WHERE 库存数量 <= 20  -- 只显示需要关注的商品
ORDER BY 库存数量 ASC;

-- 5. 日销售汇总视图
CREATE VIEW 日销售汇总视图 AS
SELECT 
    DATE(销售日期) AS 销售日期,
    COUNT(*) AS 订单总数,
    SUM(总金额) AS 销售总额,
    SUM(CASE WHEN 会员ID IS NOT NULL THEN 总金额 ELSE 0 END) AS 会员销售额,
    SUM(CASE WHEN 会员ID IS NULL THEN 总金额 ELSE 0 END) AS 非会员销售额,
    COUNT(DISTINCT 员工ID) AS 参与员工数
FROM 销售单表
GROUP BY DATE(销售日期)
ORDER BY DATE(销售日期) DESC;

-- 6. 商品销售排行视图
CREATE VIEW 商品销售排行视图 AS
SELECT 
    p.商品条码,
    p.商品名称,
    p.规格,
    SUM(d.销售数量) AS 销售总量,
    SUM(d.销售数量 * d.售价 * d.折扣率) AS 销售总额,
    SUM(d.销售数量 * (d.售价 - p.成本价) * d.折扣率) AS 毛利润,
    RANK() OVER (ORDER BY SUM(d.销售数量 * d.售价 * d.折扣率) DESC) AS 销售排名
FROM 销售明细表 d
JOIN 商品表 p ON d.商品条码 = p.商品条码
GROUP BY p.商品条码, p.商品名称, p.规格;

-- 7. 会员消费排行视图
CREATE VIEW 会员消费排行视图 AS
SELECT 
    m.会员ID,
    m.姓名,
    m.电话,
    COUNT(DISTINCT s.销售单号) AS 消费次数,
    SUM(s.总金额) AS 消费总额,
    MAX(s.销售日期) AS 最近消费日期,
    m.积分,
    m.折扣率
FROM 会员表 m
LEFT JOIN 销售单表 s ON m.会员ID = s.会员ID
GROUP BY m.会员ID, m.姓名, m.电话, m.积分, m.折扣率
ORDER BY 消费总额 DESC;







-- 删除已存在的"处理销售"存储过程，防止重复创建
DROP PROCEDURE IF EXISTS 处理销售;

-- 创建处理销售业务的存储过程
DELIMITER //  -- 临时修改分隔符为//，以便在存储过程中使用分号
CREATE PROCEDURE 处理销售(
    IN p_员工ID INT,  -- 输入参数：操作员工的ID编号
    IN p_会员ID INT,  -- 输入参数：会员ID，可为NULL表示非会员购买
    IN p_支付方式 ENUM('现金','会员卡','微信','支付宝'),  -- 输入参数：支付方式枚举值
    IN p_商品列表 JSON  -- 输入参数：JSON格式的商品列表数据
)
BEGIN
    -- 声明所有需要的变量
    DECLARE v_销售单号 INT;  -- 存储生成的销售单编号
    DECLARE v_总金额 DECIMAL(10,2) DEFAULT 0;  -- 存储订单总金额，初始化为0
    DECLARE v_折扣率 DECIMAL(3,2);  -- 存储会员折扣率(0.75-1.0)
    DECLARE i INT DEFAULT 0;  -- 循环计数器，用于遍历JSON数组
    DECLARE v_商品条码 VARCHAR(20);  -- 存储当前处理的商品条码
    DECLARE v_购买数量 INT;  -- 存储当前商品的购买数量
    DECLARE v_库存数量 INT;  -- 存储当前商品的库存数量
    DECLARE v_零售价 DECIMAL(10,2);  -- 存储当前商品的零售价格
    DECLARE v_商品名称 VARCHAR(100);  -- 存储当前商品的名称
    
    -- 获取会员折扣率：如果是会员则查询折扣率，非会员默认1.0(无折扣)
    IF p_会员ID IS NOT NULL THEN
        SELECT 折扣率 INTO v_折扣率 FROM 会员表 WHERE 会员ID = p_会员ID;
    ELSE
        SET v_折扣率 = 1.0;  -- 非会员不打折
    END IF;
    
    -- 创建销售单记录，初始总金额设为0，后面会更新
    INSERT INTO 销售单表 (销售日期, 员工ID, 会员ID, 总金额, 支付方式)
    VALUES (NOW(), p_员工ID, p_会员ID, 0, p_支付方式);
    
    -- 获取刚插入的销售单ID
    SET v_销售单号 = LAST_INSERT_ID();
    
    -- 循环处理JSON数组中的每个商品
    WHILE i < JSON_LENGTH(p_商品列表) DO
        -- 从JSON中提取商品条码(使用双引号包裹中文键名)
        SET v_商品条码 = JSON_UNQUOTE(JSON_EXTRACT(p_商品列表, CONCAT('$[', i, ']."条码"')));
        -- 从JSON中提取购买数量
        SET v_购买数量 = JSON_EXTRACT(p_商品列表, CONCAT('$[', i, ']."数量"'));
        
        -- 从商品表查询当前商品的详细信息
        SELECT 商品名称, 零售价, 库存数量 INTO v_商品名称, v_零售价, v_库存数量
        FROM 商品表 WHERE 商品条码 = v_商品条码;
        
        -- 检查库存是否足够
        IF v_库存数量 < v_购买数量 THEN
            -- 库存不足时，构造错误信息并抛出异常
            SET @error_msg = CONCAT('商品库存不足: ', v_商品名称);
            SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = @error_msg;
        END IF;
        
        -- 添加销售明细记录
        INSERT INTO 销售明细表 (销售单号, 商品条码, 销售数量, 售价, 折扣率)
        VALUES (v_销售单号, v_商品条码, v_购买数量, v_零售价, v_折扣率);
        
        -- 更新商品库存(减去已售数量)
        UPDATE 商品表 SET 库存数量 = 库存数量 - v_购买数量
        WHERE 商品条码 = v_商品条码;
        
        -- 累加计算总金额(考虑折扣)
        SET v_总金额 = v_总金额 + (v_零售价 * v_折扣率 * v_购买数量);
        
        -- 计数器加1，处理下一个商品
        SET i = i + 1;
    END WHILE;
    
    -- 更新销售单的总金额
    UPDATE 销售单表 SET 总金额 = v_总金额 WHERE 销售单号 = v_销售单号;
    
    -- 如果是会员购买，更新会员积分和消费总额
    IF p_会员ID IS NOT NULL THEN
        -- 每消费4元积1分(FLOOR取整)
        UPDATE 会员表 
        SET 积分 = 积分 + FLOOR(v_总金额/4),
            消费总额 = 消费总额 + v_总金额
        WHERE 会员ID = p_会员ID;
        
        -- 调用更新会员折扣的存储过程
        CALL 更新会员折扣(p_会员ID);
    END IF;
    
    -- 返回生成的销售单号和总金额
    SELECT v_销售单号 AS 销售单号, v_总金额 AS 总金额;
END //
DELIMITER ;  -- 恢复分隔符为分号


-- 测试数据准备
INSERT INTO 商品表(商品条码, 商品名称,成本价, 零售价, 库存数量)
VALUES ('1001', '测试商品',25.00, 50.00, 10);

-- 执行存储过程
CALL 处理销售(1, NULL, '现金', '[{"条码":"1001","数量":2}]');


-- 删除已存在的"处理进货"存储过程
DROP PROCEDURE IF EXISTS 处理进货;

-- 创建处理进货业务的存储过程
DELIMITER //
CREATE PROCEDURE 处理进货(
    IN p_员工ID INT,  -- 输入参数：操作员工ID
    IN p_供应商ID INT,  -- 输入参数：供应商ID
    IN p_商品列表 JSON  -- 输入参数：JSON格式的商品信息数组
)
BEGIN
    -- 声明变量
    DECLARE v_进货单号 INT;  -- 存储生成的进货单号
    DECLARE v_总金额 DECIMAL(10,2) DEFAULT 0;  -- 存储进货总金额
    DECLARE i INT DEFAULT 0;  -- 循环计数器
    DECLARE v_商品条码 VARCHAR(20);  -- 存储商品条码
    DECLARE v_商品名称 VARCHAR(100);  -- 存储商品名称
    DECLARE v_规格 VARCHAR(20);  -- 存储商品规格
    DECLARE v_数量 INT;  -- 存储进货数量
    DECLARE v_进价 DECIMAL(10,2);  -- 存储商品进价
    DECLARE v_零售价 DECIMAL(10,2);  -- 存储商品零售价
    
    -- 创建进货单记录，初始总金额设为0
    INSERT INTO 进货单表 (进货日期, 员工ID, 供应商ID, 总金额)
    VALUES (NOW(), p_员工ID, p_供应商ID, 0);
    
    -- 获取刚插入的进货单ID
    SET v_进货单号 = LAST_INSERT_ID();
    
    -- 循环处理每个进货商品
    WHILE i < JSON_LENGTH(p_商品列表) DO
        -- 从JSON中提取完整的商品信息
        SET v_商品条码 = JSON_UNQUOTE(JSON_EXTRACT(p_商品列表, CONCAT('$[', i, ']."条码"')));
        SET v_商品名称 = JSON_UNQUOTE(JSON_EXTRACT(p_商品列表, CONCAT('$[', i, ']."名称"')));
        SET v_规格 = JSON_UNQUOTE(JSON_EXTRACT(p_商品列表, CONCAT('$[', i, ']."规格"')));
        SET v_进价 = JSON_EXTRACT(p_商品列表, CONCAT('$[', i, ']."进价"'));
        SET v_零售价 = JSON_EXTRACT(p_商品列表, CONCAT('$[', i, ']."零售价"'));
        SET v_数量 = JSON_EXTRACT(p_商品列表, CONCAT('$[', i, ']."数量"'));
        
        -- 检查商品是否已存在
        IF NOT EXISTS (SELECT 1 FROM 商品表 WHERE 商品条码 = v_商品条码) THEN
            -- 新商品：插入完整商品信息
            INSERT INTO 商品表 (商品条码, 商品名称, 规格, 零售价, 成本价, 库存数量, 供应商ID)
            VALUES (
                v_商品条码, 
                v_商品名称,
                v_规格,
                v_零售价,
                v_进价,
                0,  -- 初始库存为0，下面会增加
                p_供应商ID
            );
        ELSE
            -- 已有商品：更新价格信息
            UPDATE 商品表 
            SET 零售价 = v_零售价,
                成本价 = v_进价
            WHERE 商品条码 = v_商品条码;
        END IF;
        
        -- 添加进货明细记录
        INSERT INTO 进货明细表 (进货单号, 商品条码, 进货数量, 进价)
        VALUES (v_进货单号, v_商品条码, v_数量, v_进价);
        
        -- 更新商品库存(增加进货数量)
        UPDATE 商品表 
        SET 库存数量 = 库存数量 + v_数量
        WHERE 商品条码 = v_商品条码;
        
        -- 累加计算总金额(进价×数量)
        SET v_总金额 = v_总金额 + (v_进价 * v_数量);
        
        -- 处理下一个商品
        SET i = i + 1;
    END WHILE;
    
    -- 更新进货单总金额
    UPDATE 进货单表 SET 总金额 = v_总金额 WHERE 进货单号 = v_进货单号;
    
    -- 返回进货单号和总金额
    SELECT v_进货单号 AS 进货单号, v_总金额 AS 总金额;
END //
DELIMITER ;


-- 创建更新会员折扣的存储过程
DELIMITER //
CREATE PROCEDURE 更新会员折扣(
    IN p_会员ID INT  -- 输入参数：需要更新折扣的会员ID
)
BEGIN
    DECLARE v_积分 INT;  -- 存储会员当前积分
    
    -- 查询会员当前积分
    SELECT 积分 INTO v_积分 FROM 会员表 WHERE 会员ID = p_会员ID;
    
    -- 根据积分设置不同的折扣等级
    UPDATE 会员表 
    SET 折扣率 = CASE 
        WHEN v_积分 >= 1000 THEN 0.75   -- 钻石会员：75折
        WHEN v_积分 >= 500 THEN 0.85    -- 黄金会员：85折
        WHEN v_积分 >= 200 THEN 0.9     -- 白银会员：9折
        WHEN v_积分 >= 100 THEN 0.95    -- 普通会员：95折
        ELSE 1.0                        -- 新会员：无折扣
    END
    WHERE 会员ID = p_会员ID;
END //
DELIMITER ;


-- 安全删除商品：保留已经产生进货或销售历史的商品
DELIMITER //
CREATE PROCEDURE 删除商品(IN p_商品条码 VARCHAR(20))
BEGIN
    IF NOT EXISTS (SELECT 1 FROM 商品表 WHERE 商品条码 = p_商品条码) THEN
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = '商品不存在或已被删除';
    END IF;

    IF EXISTS (SELECT 1 FROM 销售明细表 WHERE 商品条码 = p_商品条码)
       OR EXISTS (SELECT 1 FROM 进货明细表 WHERE 商品条码 = p_商品条码) THEN
        SIGNAL SQLSTATE '45000'
            SET MESSAGE_TEXT = '该商品已有销售或进货记录，为保证历史数据完整性不能删除';
    END IF;

    DELETE FROM 商品表 WHERE 商品条码 = p_商品条码;
END //
DELIMITER ;

-- 安全删除会员：保留已经产生消费历史的会员
DELIMITER //
CREATE PROCEDURE 删除会员(IN p_会员ID INT)
BEGIN
    IF NOT EXISTS (SELECT 1 FROM 会员表 WHERE 会员ID = p_会员ID) THEN
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = '会员不存在或已被删除';
    END IF;

    IF EXISTS (SELECT 1 FROM 销售单表 WHERE 会员ID = p_会员ID) THEN
        SIGNAL SQLSTATE '45000'
            SET MESSAGE_TEXT = '该会员已有消费记录，为保证历史数据完整性不能删除';
    END IF;

    DELETE FROM 会员表 WHERE 会员ID = p_会员ID;
END //
DELIMITER ;


-- 创建商品价格检查触发器
DELIMITER //
CREATE TRIGGER 检查商品价格
BEFORE UPDATE ON 商品表  -- 在更新商品表前触发
FOR EACH ROW  -- 对每行数据执行
BEGIN
    -- 确保更新后的零售价不低于成本价
    IF NEW.零售价 < NEW.成本价 THEN
        -- 如果低于成本价，抛出错误
        SIGNAL SQLSTATE '45000' 
        SET MESSAGE_TEXT = '零售价不能低于成本价';
    END IF;
END //
DELIMITER ;

-- 创建库存预警触发器（在商品表更新后检查库存量）
DELIMITER //
CREATE TRIGGER 库存预警检查
AFTER UPDATE ON 商品表
FOR EACH ROW
BEGIN
    DECLARE v_预警消息 VARCHAR(100);
    
    -- 检查库存状态
    IF NEW.库存数量 <= 10 THEN
        SET v_预警消息 = CONCAT('商品 ', NEW.商品名称, ' 库存严重不足(剩余:', NEW.库存数量, ')，请立即补货！');
        -- 这里可以插入预警日志表或发送通知（实际应用中）
        SIGNAL SQLSTATE '01000' SET MESSAGE_TEXT = v_预警消息;
    ELSEIF NEW.库存数量 <= 20 THEN
        SET v_预警消息 = CONCAT('商品 ', NEW.商品名称, ' 库存紧张(剩余:', NEW.库存数量, ')，建议补货');
        SIGNAL SQLSTATE '01000' SET MESSAGE_TEXT = v_预警消息;
    END IF;
END //
DELIMITER ;


-- 创建系统用户
CREATE USER '收银员'@'localhost' IDENTIFIED BY 'cashier123';  -- 收银员账户
CREATE USER '库存员'@'localhost' IDENTIFIED BY 'stock123';  -- 库存管理员账户
CREATE USER '经理'@'localhost' IDENTIFIED BY 'manager123';  -- 经理账户

-- 设置收银员权限
GRANT SELECT, INSERT ON 超市销售管理系统.销售单表 TO '收银员'@'localhost';  -- 销售单表权限
GRANT SELECT, INSERT ON 超市销售管理系统.销售明细表 TO '收银员'@'localhost';  -- 销售明细表权限
GRANT SELECT ON 超市销售管理系统.商品表 TO '收银员'@'localhost';  -- 商品查询权限
GRANT SELECT ON 超市销售管理系统.会员表 TO '收银员'@'localhost';  -- 会员查询权限
GRANT EXECUTE ON PROCEDURE 超市销售管理系统.处理销售 TO '收银员'@'localhost';  -- 执行销售流程权限
GRANT EXECUTE ON PROCEDURE 超市销售管理系统.删除会员 TO '收银员'@'localhost';  -- 删除无消费记录的会员
GRANT SELECT ON `超市销售管理系统`.* TO '收银员'@'localhost';   -- 所有select权限

-- 设置库存管理员权限
GRANT SELECT, INSERT, UPDATE ON 超市销售管理系统.商品表 TO '库存员'@'localhost';  -- 商品管理权限
GRANT SELECT, INSERT ON 超市销售管理系统.进货单表 TO '库存员'@'localhost';  -- 进货单权限
GRANT SELECT, INSERT ON 超市销售管理系统.进货明细表 TO '库存员'@'localhost';  -- 进货明细权限
GRANT SELECT ON 超市销售管理系统.供应商表 TO '库存员'@'localhost';  -- 供应商查询权限
GRANT EXECUTE ON PROCEDURE 超市销售管理系统.处理进货 TO '库存员'@'localhost';  -- 执行进货流程权限
GRANT EXECUTE ON PROCEDURE 超市销售管理系统.删除商品 TO '库存员'@'localhost';  -- 删除无业务历史的商品
GRANT SELECT ON `超市销售管理系统`.* TO '库存员'@'localhost';   -- 所有select权限

-- 设置经理权限(所有权限)
GRANT ALL PRIVILEGES ON 超市销售管理系统.* TO '经理'@'localhost';





SELECT USER, HOST FROM mysql.user;


-- 数据插入
-- 1.插入员工数据
INSERT INTO 员工表 (姓名, 性别, 电话, 角色, 用户名, 密码) VALUES
('张经理', '男', '13800138001', '经理', 'manager', MD5('manager123')),
('李收银', '女', '13800138002', '收银员', 'cashier1', MD5('cashier123')),
('王收银', '女', '13800138003', '收银员', 'cashier2', MD5('cashier123')),
('赵库存', '男', '13800138004', '库存管理员', 'stock1', MD5('stock123')),
('钱库存', '女', '13800138005', '库存管理员', 'stock2', MD5('stock123'));

-- 2. 插入供应商数据
-- 插入供应商数据
INSERT INTO 供应商表 (名称, 联系人, 联系电话) VALUES
('农夫山泉有限公司', '张经理', '400-1234567'),
('康师傅食品集团', '李主管', '400-7654321'),
('蒙牛乳业', '王总监', '400-1112222'),
('海天调味品', '赵经理', '400-3334444'),
('金锣肉制品', '钱主管', '400-5556666');

-- 3. 插入会员数据
-- 插入会员数据
INSERT INTO 会员表 (姓名, 电话, 积分, 消费总额, 折扣率, 注册日期) VALUES
('黄金会员', '13900139001', 600, 2500.00, 0.85, '2023-01-15'),
('白银会员', '13900139002', 300, 1200.00, 0.9, '2023-03-20'),
('钻石会员', '13900139003', 1200, 5000.00, 0.75, '2022-11-05'),
('新会员', '13900139004', 50, 200.00, 1.0, '2023-05-10'),
('普通会员', '13900139005', 150, 600.00, 0.95, '2023-04-01');

-- 4. 插入商品数据
-- 插入商品数据
INSERT INTO 商品表 (商品条码, 商品名称, 规格, 零售价, 成本价, 库存数量, 供应商ID) VALUES
('6901285991219', '农夫山泉矿泉水', '550ml', 2.00, 1.20, 100, 1),
('6928804010013', '康师傅红烧牛肉面', '桶装', 4.50, 2.80, 80, 2),
('6928804010020', '康师傅香辣牛肉面', '桶装', 4.50, 2.80, 75, 2),
('6938888888816', '蒙牛纯牛奶', '250ml*12', 48.00, 35.00, 50, 3),
('6938888888823', '蒙牛高钙奶', '250ml*12', 52.00, 38.00, 45, 3),
('6922734280808', '海天酱油', '500ml', 12.00, 8.50, 60, 4),
('6922734280815', '海天老抽', '500ml', 11.00, 7.80, 55, 4),
('6922734280822', '海天蚝油', '500g', 15.00, 10.50, 40, 4),
('6927462201234', '金锣火腿肠', '40g*10', 15.00, 10.00, 70, 5),
('6927462201241', '金锣王中王', '40g*10', 18.00, 12.50, 65, 5),
('6927462201258', '金锣鸡肉肠', '40g*10', 14.00, 9.50, 60, 5),
('6925303774012', '可口可乐', '330ml', 3.00, 1.80, 120, NULL),
('6925303774029', '雪碧', '330ml', 3.00, 1.80, 110, NULL),
('6925303774036', '芬达橙味', '330ml', 3.00, 1.80, 100, NULL),
('6954767418521', '奥利奥夹心饼干', '116g', 6.50, 4.20, 90, NULL),
('6954767418538', '奥利奥巧克力味', '116g', 6.50, 4.20, 85, NULL),
('6954767418545', '奥利奥草莓味', '116g', 6.50, 4.20, 80, NULL),
('6922266445577', '清风抽纸', '3层100抽*6包', 18.00, 12.00, 60, NULL),
('6922266445584', '清风卷纸', '10卷', 25.00, 16.00, 55, NULL);


-- 5. 插入进货单数据
-- 插入进货单数据
-- 进货单1
INSERT INTO 进货单表 (进货日期, 员工ID, 供应商ID, 总金额) VALUES
('2023-05-01 09:00:00', 4, 1, 1200.00);

INSERT INTO 进货明细表 (进货单号, 商品条码, 进货数量, 进价) VALUES
(1, '6901285991219', 1000, 1.20);

-- 进货单2
INSERT INTO 进货单表 (进货日期, 员工ID, 供应商ID, 总金额) VALUES
('2023-05-02 10:00:00', 5, 2, 1120.00);

INSERT INTO 进货明细表 (进货单号, 商品条码, 进货数量, 进价) VALUES
(2, '6928804010013', 200, 2.80),
(2, '6928804010020', 200, 2.80);

-- 进货单3
INSERT INTO 进货单表 (进货日期, 员工ID, 供应商ID, 总金额) VALUES
('2023-05-03 11:00:00', 4, 3, 3650.00);

INSERT INTO 进货明细表 (进货单号, 商品条码, 进货数量, 进价) VALUES
(3, '6938888888816', 50, 35.00),
(3, '6938888888823', 50, 38.00);

-- 进货单4
INSERT INTO 进货单表 (进货日期, 员工ID, 供应商ID, 总金额) VALUES
('2023-05-04 14:00:00', 5, 4, 1860.00);

INSERT INTO 进货明细表 (进货单号, 商品条码, 进货数量, 进价) VALUES
(4, '6922734280808', 100, 8.50),
(4, '6922734280815', 100, 7.80),
(4, '6922734280822', 100, 10.50);

-- 进货单5
INSERT INTO 进货单表 (进货日期, 员工ID, 供应商ID, 总金额) VALUES
('2023-05-05 15:00:00', 4, 5, 3200.00);

INSERT INTO 进货明细表 (进货单号, 商品条码, 进货数量, 进价) VALUES
(5, '6927462201234', 200, 10.00),
(5, '6927462201241', 200, 12.50),
(5, '6927462201258', 200, 9.50);



-- 6. 插入销售单数据
-- 插入销售单数据
-- 销售单1 (非会员)
INSERT INTO 销售单表 (销售日期, 员工ID, 会员ID, 总金额, 支付方式) VALUES
('2023-05-10 08:30:15', 2, NULL, 14.50, '现金');

INSERT INTO 销售明细表 (销售单号, 商品条码, 销售数量, 售价, 折扣率) VALUES
(1, '6901285991219', 2, 2.00, 1.0),
(1, '6925303774012', 1, 3.00, 1.0),
(1, '6954767418521', 1, 6.50, 1.0);

-- 销售单2 (黄金会员)
INSERT INTO 销售单表 (销售日期, 员工ID, 会员ID, 总金额, 支付方式) VALUES
('2023-05-10 09:45:22', 2, 1, 68.85, '会员卡');

INSERT INTO 销售明细表 (销售单号, 商品条码, 销售数量, 售价, 折扣率) VALUES
(2, '6938888888816', 1, 48.00, 0.85),
(2, '6927462201241', 1, 18.00, 0.85),
(2, '6922734280808', 1, 12.00, 0.85);

-- 销售单3 (白银会员)
INSERT INTO 销售单表 (销售日期, 员工ID, 会员ID, 总金额, 支付方式) VALUES
('2023-05-10 11:20:33', 3, 2, 42.30, '微信');

INSERT INTO 销售明细表 (销售单号, 商品条码, 销售数量, 售价, 折扣率) VALUES
(3, '6928804010013', 2, 4.50, 0.9),
(3, '6928804010020', 2, 4.50, 0.9),
(3, '6925303774029', 3, 3.00, 0.9),
(3, '6954767418538', 2, 6.50, 0.9);

-- 销售单4 (钻石会员)
INSERT INTO 销售单表 (销售日期, 员工ID, 会员ID, 总金额, 支付方式) VALUES
('2023-05-10 14:15:44', 3, 3, 108.75, '支付宝');

INSERT INTO 销售明细表 (销售单号, 商品条码, 销售数量, 售价, 折扣率) VALUES
(4, '6938888888823', 2, 52.00, 0.75),
(4, '6927462201234', 1, 15.00, 0.75),
(4, '6922734280822', 1, 15.00, 0.75),
(4, '6922266445577', 1, 18.00, 0.75);

-- 销售单5 (新会员)
INSERT INTO 销售单表 (销售日期, 员工ID, 会员ID, 总金额, 支付方式) VALUES
('2023-05-10 16:30:55', 2, 4, 25.00, '现金');

INSERT INTO 销售明细表 (销售单号, 商品条码, 销售数量, 售价, 折扣率) VALUES
(5, '6925303774036', 2, 3.00, 1.0),
(5, '6954767418545', 1, 6.50, 1.0),
(5, '6927462201258', 1, 14.00, 1.0);

-- 销售单6 (普通会员)
INSERT INTO 销售单表 (销售日期, 员工ID, 会员ID, 总金额, 支付方式) VALUES
('2023-05-10 17:45:12', 3, 5, 47.50, '微信');

INSERT INTO 销售明细表 (销售单号, 商品条码, 销售数量, 售价, 折扣率) VALUES
(6, '6922734280815', 2, 11.00, 0.95),
(6, '6925303774012', 3, 3.00, 0.95),
(6, '6922266445584', 1, 25.00, 0.95);

-- 销售单7 (非会员)
INSERT INTO 销售单表 (销售日期, 员工ID, 会员ID, 总金额, 支付方式) VALUES
('2023-05-10 18:30:18', 2, NULL, 37.00, '现金');

INSERT INTO 销售明细表 (销售单号, 商品条码, 销售数量, 售价, 折扣率) VALUES
(7, '6928804010013', 3, 4.50, 1.0),
(7, '6928804010020', 2, 4.50, 1.0),
(7, '6901285991219', 5, 2.00, 1.0),
(7, '6925303774029', 2, 3.00, 1.0);



-- 插入库存紧张的商品数据（库存量<=20）
INSERT INTO 商品表 (商品条码, 商品名称, 规格, 零售价, 成本价, 库存数量, 供应商ID) VALUES
('6900000000001', '乐事薯片原味', '75g', 6.00, 4.00, 8, NULL),      -- 红色预警(库存<=10)
('6900000000002', '乐事薯片烧烤味', '75g', 6.00, 4.00, 5, NULL),   -- 红色预警
('6900000000003', '乐事薯片黄瓜味', '75g', 6.00, 4.00, 3, NULL),   -- 红色预警
('6900000000004', '德芙巧克力', '43g', 8.50, 5.50, 12, NULL),      -- 黄色预警(10<库存<=20)
('6900000000005', '士力架花生夹心', '50g', 5.00, 3.20, 15, NULL),  -- 黄色预警
('6900000000006', '绿箭口香糖', '12片', 3.50, 2.00, 18, NULL),     -- 黄色预警
('6900000000007', '益达口香糖', '10粒', 4.00, 2.50, 20, NULL),     -- 黄色预警(刚好20)
('6900000000008', '炫迈口香糖', '8片', 5.00, 3.00, 2, NULL);      -- 红色预警

-- 更新已有商品库存为预警状态
UPDATE 商品表 SET 库存数量 = 9 WHERE 商品条码 = '6954767418545';  -- 奥利奥草莓味(红色预警)
UPDATE 商品表 SET 库存数量 = 15 WHERE 商品条码 = '6922734280822'; -- 海天蚝油(黄色预警)
UPDATE 商品表 SET 库存数量 = 7 WHERE 商品条码 = '6927462201258';  -- 金锣鸡肉肠(红色预警)


-- 添加新供应商到供应商表
INSERT INTO 供应商表 (名称, 联系人, 联系电话) VALUES
('亿滋国际', '张经理', '400-1112222'),       -- 奥利奥、炫迈等
('可口可乐公司', '李主管', '400-2223333'),   -- 可乐、雪碧、芬达
('箭牌糖果', '王总监', '400-3334444'),       -- 绿箭、益达
('玛氏食品', '赵经理', '400-4445555'),       -- 德芙、士力架
('百事食品', '钱主管', '400-5556666'),       -- 乐事薯片
('维达国际', '孙经理', '400-6667777');       -- 清风

-- 先查询新添加的供应商ID
SELECT * FROM 供应商表 WHERE 名称 IN ('亿滋国际','可口可乐公司','箭牌糖果','玛氏食品','百事食品','维达国际');

-- 然后更新商品表 (假设新供应商ID从6开始)
UPDATE 商品表 SET 供应商ID = 1 WHERE 商品条码 = '6901285991219';  -- 农夫山泉
UPDATE 商品表 SET 供应商ID = 2 WHERE 商品条码 IN ('6928804010013','6928804010020'); -- 康师傅
UPDATE 商品表 SET 供应商ID = 3 WHERE 商品条码 IN ('6938888888816','6938888888823'); -- 蒙牛
UPDATE 商品表 SET 供应商ID = 4 WHERE 商品条码 IN ('6922734280808','6922734280815','6922734280822'); -- 海天
UPDATE 商品表 SET 供应商ID = 5 WHERE 商品条码 IN ('6927462201234','6927462201241','6927462201258'); -- 金锣

-- 新供应商
UPDATE 商品表 SET 供应商ID = 6 WHERE 商品名称 LIKE '%奥利奥%' OR 商品名称 = '炫迈口香糖';  -- 亿滋国际
UPDATE 商品表 SET 供应商ID = 7 WHERE 商品名称 IN ('可口可乐','雪碧','芬达橙味');  -- 可口可乐公司
UPDATE 商品表 SET 供应商ID = 8 WHERE 商品名称 IN ('绿箭口香糖','益达口香糖');  -- 箭牌糖果
UPDATE 商品表 SET 供应商ID = 9 WHERE 商品名称 IN ('德芙巧克力','士力架花生夹心');  -- 玛氏食品
UPDATE 商品表 SET 供应商ID = 10 WHERE 商品名称 LIKE '%乐事%';  -- 百事食品
UPDATE 商品表 SET 供应商ID = 11 WHERE 商品名称 LIKE '%清风%';  -- 维达国际


-- 由于销售单插入后会员积分和折扣率已经通过触发器更新，这里不需要额外操作
-- 但可以检查一下会员表数据
SELECT * FROM 会员表;
