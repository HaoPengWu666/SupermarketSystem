USE 超市销售管理系统;

DROP PROCEDURE IF EXISTS 删除商品;
DROP PROCEDURE IF EXISTS 删除会员;

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

GRANT EXECUTE ON PROCEDURE 超市销售管理系统.删除商品 TO '库存员'@'localhost';
GRANT EXECUTE ON PROCEDURE 超市销售管理系统.删除会员 TO '收银员'@'localhost';
FLUSH PRIVILEGES;
