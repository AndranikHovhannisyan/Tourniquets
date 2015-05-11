-- phpMyAdmin SQL Dump
-- version 4.0.10deb1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: May 11, 2015 at 10:28 PM
-- Server version: 5.5.40-0ubuntu0.14.04.1
-- PHP Version: 5.5.9-1ubuntu4.5

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `tourniquets`
--

DELIMITER $$
--
-- Procedures
--
CREATE DEFINER=`root`@`localhost` PROCEDURE `statistic`(department_id INT, employer_id INT, date_from DATE, date_to DATE)
BEGIN


SELECT d.name, CONCAT(e.firstname, ' ', e.lastname), DATE(tt1.date_time),

CASE
WHEN (TIMEDIFF(TIME(tt1.date_time), TIME(sh.standart_in_time)) < TIME(sh_ty.allow_lag)) AND
     (TIMEDIFF(TIME(sh.standart_in_time), TIME(tt1.date_time)) < TIME(sh_ty.ignore_time))
THEN TIME(sh.standart_in_time)
ELSE TIME(tt1.date_time)
END as in_time,

CASE
WHEN (TIMEDIFF(TIME(tt2.date_time), TIME(sh.standart_out_time)) < TIME(sh_ty.ignore_time)) AND
     (TIMEDIFF(TIME(sh.standart_out_time), TIME(tt2.date_time)) < TIME(sh_ty.allow_lag))
THEN TIME(sh.standart_out_time)
ELSE TIME(tt2.date_time)
END as out_time,

TIMEDIFF(
    CASE
    WHEN (TIMEDIFF(TIME(tt2.date_time), TIME(sh.standart_out_time)) < TIME(sh_ty.ignore_time)) AND
         (TIMEDIFF(TIME(sh.standart_out_time), TIME(tt2.date_time)) < TIME(sh_ty.allow_lag))
    THEN TIME(sh.standart_out_time)
    ELSE TIME(tt2.date_time)
    END,

    CASE
    WHEN (TIMEDIFF(TIME(tt1.date_time), TIME(sh.standart_in_time)) < TIME(sh_ty.allow_lag)) AND
         (TIMEDIFF(TIME(sh.standart_in_time), TIME(tt1.date_time)) < TIME(sh_ty.ignore_time))
    THEN TIME(sh.standart_in_time)
    ELSE TIME(tt1.date_time)
    END
) as workingTime,



TIMEDIFF(
    TIME(sh.standart_in_time),

    CASE
    WHEN (TIMEDIFF(TIME(tt1.date_time), TIME(sh.standart_in_time)) < TIME(sh_ty.allow_lag)) AND
         (TIMEDIFF(TIME(sh.standart_in_time), TIME(tt1.date_time)) < TIME(sh_ty.ignore_time))
    THEN TIME(sh.standart_in_time)
    ELSE TIME(tt1.date_time)
    END
) as inViolation,

TIMEDIFF(
    CASE
    WHEN (TIMEDIFF(TIME(tt2.date_time), TIME(sh.standart_out_time)) < TIME(sh_ty.ignore_time)) AND
         (TIMEDIFF(TIME(sh.standart_out_time), TIME(tt2.date_time)) < TIME(sh_ty.allow_lag))
    THEN TIME(sh.standart_out_time)
    ELSE TIME(tt2.date_time)
    END,

    TIME(sh.standart_out_time)

) as outViolation


FROM tourniquet_transaction as tt1

JOIN employer_employer_ids as eei
ON tt1.emp_number = eei.emp_number AND eei.to IS NULL

JOIN employer as e
ON eei.employer_id = e.id

JOIN employer_dep_positions as edp
ON e.id = edp.employer_id AND edp.to IS NULL

JOIN dep_positions as dp
ON edp.dep_positions_id = dp.id

JOIN department as d
ON dp.department_id = d.id

JOIN tourniquet_transaction as tt2
ON DATE(tt1.date_time) = DATE(tt1.date_time) AND tt1.emp_number = tt2.emp_number

JOIN tourniquet as t1
ON tt1.tourniquet_number = t1.number AND t1.type = 0

JOIN tourniquet as t2
ON tt2.tourniquet_number = t2.number AND t2.type = 1

JOIN schedule as sh
ON e.schedule_id = sh.id

JOIN schedule_type as sh_ty
ON sh.schedule_type_id = sh_ty.id

WHERE (department_id = 0 OR d.id = department_id)
AND (employer_id = 0 OR e.id = employer_id)
AND (date_from IS NULL OR DATE(tt1.date_time) >= date_from)
AND (date_to IS NULL OR DATE(tt1.date_time) <= date_to);

END$$

DELIMITER ;

-- --------------------------------------------------------

--
-- Table structure for table `address`
--

CREATE TABLE IF NOT EXISTS `address` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `country` varchar(45) DEFAULT NULL,
  `city` varchar(45) DEFAULT NULL,
  `street` varchar(45) DEFAULT NULL,
  `h_number` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=37 ;

--
-- Dumping data for table `address`
--

INSERT INTO `address` (`id`, `country`, `city`, `street`, `h_number`) VALUES
(31, 'Հայաստան', 'Երևան', 'Մայիսի 9', '8/28'),
(32, 'Հայաստան', 'Ջերմուկ', 'Բաղրամյան', '12/5'),
(33, 'Հայաստան', 'Երևան', 'Տիչինա', '25/6'),
(34, 'Հայաստան', 'Երևան', 'Գրիբոյեդով', '25/9ա'),
(35, 'Հայաստան', 'Երևան', 'Երվանդ Ք․', '12/9'),
(36, 'Հայստան', 'Տաշիր', 'Ազատության', '32');

-- --------------------------------------------------------

--
-- Table structure for table `department`
--

CREATE TABLE IF NOT EXISTS `department` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(45) DEFAULT NULL,
  `schedule_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `fk_department_schedule1_idx` (`schedule_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=26 ;

--
-- Dumping data for table `department`
--

INSERT INTO `department` (`id`, `name`, `schedule_id`) VALUES
(25, 'Կառավարման տեխնոլոգիաներ', 2);

-- --------------------------------------------------------

--
-- Table structure for table `dep_positions`
--

CREATE TABLE IF NOT EXISTS `dep_positions` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `department_id` int(11) NOT NULL,
  `position_id` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `department_id` (`department_id`,`position_id`),
  KEY `fk_dep_positions_department1_idx` (`department_id`),
  KEY `fk_dep_positions_position1` (`position_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=11 ;

--
-- Dumping data for table `dep_positions`
--

INSERT INTO `dep_positions` (`id`, `department_id`, `position_id`) VALUES
(7, 25, 13),
(8, 25, 14),
(9, 25, 16),
(10, 25, 18);

-- --------------------------------------------------------

--
-- Table structure for table `employer`
--

CREATE TABLE IF NOT EXISTS `employer` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `firstname` varchar(45) DEFAULT NULL,
  `lastname` varchar(45) DEFAULT NULL,
  `middlename` varchar(45) DEFAULT NULL,
  `birth_date` date DEFAULT NULL,
  `passport_series` varchar(2) DEFAULT NULL,
  `passport_number` varchar(10) DEFAULT NULL,
  `given_date` date DEFAULT NULL,
  `given_from` varchar(3) DEFAULT NULL,
  `gender` varchar(45) DEFAULT NULL,
  `is_conscript` tinyint(1) DEFAULT NULL,
  `family_status` varchar(45) DEFAULT NULL,
  `children_num` int(11) DEFAULT NULL,
  `minor_children_num` int(11) DEFAULT NULL,
  `register_address_id` int(11) DEFAULT NULL,
  `living_address_id` int(11) DEFAULT NULL,
  `schedule_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `fk_employeer_address1_idx` (`register_address_id`),
  KEY `fk_employeer_address2_idx` (`living_address_id`),
  KEY `fk_employeer_schedule1_idx` (`schedule_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=36 ;

--
-- Dumping data for table `employer`
--

INSERT INTO `employer` (`id`, `firstname`, `lastname`, `middlename`, `birth_date`, `passport_series`, `passport_number`, `given_date`, `given_from`, `gender`, `is_conscript`, `family_status`, `children_num`, `minor_children_num`, `register_address_id`, `living_address_id`, `schedule_id`) VALUES
(29, 'Անդրանիկ', 'Հովհաննիսյան', 'Մկրտիչի', '2090-08-02', 'AH', '123456789', '2008-01-01', '003', '0', 1, '2', 0, 0, 31, 31, 10),
(31, 'Հազարապետ', 'Թունանյան', 'Անդրանիկ', '2093-02-22', 'AH', '123654789', '2001-05-12', '006', '0', 0, '2', 0, 0, 32, 33, 10),
(32, 'Վազգեն', 'Մանուկյան', '', '2085-02-03', 'AH', '785693211', '2002-05-25', '008', '0', 1, '1', 3, 3, 34, 34, 2),
(33, 'Սարգիս', 'Մանուկյան', '', '2089-04-06', 'AH', '665522352', '2003-05-25', '007', '0', 1, '1', 1, 1, 35, 35, 2),
(34, 'Սյուզի', 'Սուքիասյան', '', '2093-06-28', 'AH', '632225511', '2005-07-21', '023', '1', 0, '2', 0, 0, 36, 35, 10),
(35, 'Անի', 'Մանուկյան', '', '2089-02-03', 'AH', '12385269', '2002-05-25', '008', '1', 0, '1', 0, 0, 35, 35, 2);

-- --------------------------------------------------------

--
-- Table structure for table `employer_dep_positions`
--

CREATE TABLE IF NOT EXISTS `employer_dep_positions` (
  `employer_id` int(11) NOT NULL,
  `dep_positions_id` int(11) NOT NULL,
  `from` date DEFAULT NULL,
  `to` date DEFAULT NULL,
  `id` int(11) NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`id`),
  KEY `fk_employer_has_dep_positions_dep_positions1_idx` (`dep_positions_id`),
  KEY `fk_employer_has_dep_positions_employer1_idx` (`employer_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=7 ;

--
-- Dumping data for table `employer_dep_positions`
--

INSERT INTO `employer_dep_positions` (`employer_id`, `dep_positions_id`, `from`, `to`, `id`) VALUES
(29, 10, '2015-05-05', NULL, 1),
(31, 10, '2015-05-05', NULL, 2),
(32, 8, '2015-05-05', NULL, 3),
(33, 7, '2015-05-05', NULL, 4),
(34, 9, '2015-05-05', NULL, 5),
(35, 10, '2015-05-11', NULL, 6);

-- --------------------------------------------------------

--
-- Table structure for table `employer_employer_ids`
--

CREATE TABLE IF NOT EXISTS `employer_employer_ids` (
  `employer_id` int(11) NOT NULL,
  `from` date DEFAULT NULL,
  `to` varchar(45) DEFAULT NULL,
  `emp_number` varchar(15) NOT NULL,
  `id` int(11) NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`id`),
  KEY `fk_employer_ids_has_employer_employer1_idx` (`employer_id`),
  KEY `fk_employer_employer_ids_employer_ids1_idx` (`emp_number`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=14 ;

--
-- Dumping data for table `employer_employer_ids`
--

INSERT INTO `employer_employer_ids` (`employer_id`, `from`, `to`, `emp_number`, `id`) VALUES
(29, '2015-05-05', NULL, '123', 1),
(31, '2015-05-05', NULL, '456', 2),
(32, '2015-05-05', NULL, '774', 3),
(33, '2015-05-05', NULL, '852', 4),
(34, '2015-05-05', NULL, '451', 5),
(35, '2015-05-11', '2015-5-11', '745', 6),
(35, '2015-05-11', '2015-5-11', '741', 7),
(35, '2015-05-11', '2015-5-11', '745', 8),
(35, '2015-05-11', '2015-5-11', '111', 9),
(35, '2015-05-11', '2015-5-11', '888', 10),
(35, '2015-05-11', '2015-5-11', '887', 11),
(35, '2015-05-11', NULL, '999', 12),
(35, '2015-05-11', NULL, '444', 13);

-- --------------------------------------------------------

--
-- Table structure for table `employer_ids`
--

CREATE TABLE IF NOT EXISTS `employer_ids` (
  `emp_number` varchar(15) NOT NULL,
  `id_type` int(11) NOT NULL,
  PRIMARY KEY (`emp_number`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `employer_ids`
--

INSERT INTO `employer_ids` (`emp_number`, `id_type`) VALUES
('111', 0),
('123', 0),
('444', 1),
('451', 0),
('456', 0),
('741', 1),
('745', 0),
('774', 0),
('852', 0),
('887', 0),
('888', 1),
('999', 0);

-- --------------------------------------------------------

--
-- Table structure for table `employer_phone_number`
--

CREATE TABLE IF NOT EXISTS `employer_phone_number` (
  `employer_id` int(11) NOT NULL,
  `from` date DEFAULT NULL,
  `to` date DEFAULT NULL,
  `phone_number` varchar(20) NOT NULL DEFAULT '',
  PRIMARY KEY (`phone_number`),
  KEY `fk_phone_number_has_employer_employer1_idx` (`employer_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `employer_phone_number`
--

INSERT INTO `employer_phone_number` (`employer_id`, `from`, `to`, `phone_number`) VALUES
(29, '2009-08-02', '2000-01-01', '+374441995'),
(31, '2006-01-01', '2000-01-01', '+37498444192');

-- --------------------------------------------------------

--
-- Table structure for table `original_tourniquet_transaction`
--

CREATE TABLE IF NOT EXISTS `original_tourniquet_transaction` (
  `date_time` datetime NOT NULL,
  `tourniquet_number` int(11) NOT NULL,
  `emp_number` varchar(20) NOT NULL,
  `id` int(11) NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`id`),
  KEY `tourniquet_id` (`tourniquet_number`,`emp_number`),
  KEY `emp_number` (`emp_number`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=29 ;

--
-- Dumping data for table `original_tourniquet_transaction`
--

INSERT INTO `original_tourniquet_transaction` (`date_time`, `tourniquet_number`, `emp_number`, `id`) VALUES
('2015-05-10 09:00:00', 1, '123', 17),
('2015-05-10 09:05:00', 1, '444', 18),
('2015-05-10 09:10:00', 1, '451', 19),
('2015-05-10 09:15:00', 1, '456', 20),
('2015-05-10 10:00:00', 1, '774', 21),
('2015-05-10 10:30:00', 1, '852', 22),
('2015-05-10 18:00:00', 2, '123', 23),
('2015-05-10 18:05:00', 2, '444', 24),
('2015-05-10 18:10:00', 2, '451', 25),
('2015-05-10 18:15:00', 2, '456', 26),
('2015-05-10 19:00:00', 2, '774', 27),
('2015-05-10 19:30:00', 2, '852', 28);

--
-- Triggers `original_tourniquet_transaction`
--
DROP TRIGGER IF EXISTS `aftre_transaction_import`;
DELIMITER //
CREATE TRIGGER `aftre_transaction_import` AFTER INSERT ON `original_tourniquet_transaction`
 FOR EACH ROW BEGIN
	INSERT INTO tourniquet_transaction (date_time, tourniquet_number, emp_number) 
		   VALUES (NEW.date_time, NEW.tourniquet_number, NEW.emp_number);
END
//
DELIMITER ;

-- --------------------------------------------------------

--
-- Table structure for table `position`
--

CREATE TABLE IF NOT EXISTS `position` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '	',
  `name` varchar(45) DEFAULT NULL,
  `schedule_id` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `fk_position_schedule1_idx` (`schedule_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=20 ;

--
-- Dumping data for table `position`
--

INSERT INTO `position` (`id`, `name`, `schedule_id`) VALUES
(13, 'Տնօրեն', 1),
(14, 'Փոխտնօրեն', 1),
(15, 'Քարտուղար', 1),
(16, 'Հաշվապահ', 1),
(17, 'Պահակ', 3),
(18, 'Ծրագրավորող', 1),
(19, 'Դասախոս', 1);

-- --------------------------------------------------------

--
-- Table structure for table `schedule`
--

CREATE TABLE IF NOT EXISTS `schedule` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `standart_in_time` time DEFAULT NULL,
  `standart_out_time` time DEFAULT NULL,
  `mon_in` time DEFAULT NULL,
  `mon_out` time DEFAULT NULL,
  `thsd_in` time DEFAULT NULL,
  `thsd_out` time DEFAULT NULL,
  `wed_in` time DEFAULT NULL,
  `wed_out` time DEFAULT NULL,
  `thrsd_in` time DEFAULT NULL,
  `thrsd_out` time DEFAULT NULL,
  `fri_in` time DEFAULT NULL,
  `fri_out` time DEFAULT NULL,
  `sat_in` time DEFAULT NULL,
  `sat_out` time DEFAULT NULL,
  `sun_in` time DEFAULT NULL,
  `sun_out` time DEFAULT NULL,
  `interval_in_days` int(11) DEFAULT NULL,
  `schedule_type_id` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `fk_schedule_schedule_type1_idx` (`schedule_type_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=12 ;

--
-- Dumping data for table `schedule`
--

INSERT INTO `schedule` (`id`, `standart_in_time`, `standart_out_time`, `mon_in`, `mon_out`, `thsd_in`, `thsd_out`, `wed_in`, `wed_out`, `thrsd_in`, `thrsd_out`, `fri_in`, `fri_out`, `sat_in`, `sat_out`, `sun_in`, `sun_out`, `interval_in_days`, `schedule_type_id`) VALUES
(2, '09:00:00', '18:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', 0, 3),
(10, '15:00:00', '19:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', 0, 7),
(11, '14:00:00', '18:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', 0, 7);

-- --------------------------------------------------------

--
-- Table structure for table `schedule_type`
--

CREATE TABLE IF NOT EXISTS `schedule_type` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(45) DEFAULT NULL,
  `allow_lag` time DEFAULT NULL,
  `ignore_time` time DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=9 ;

--
-- Dumping data for table `schedule_type`
--

INSERT INTO `schedule_type` (`id`, `name`, `allow_lag`, `ignore_time`) VALUES
(3, 'Ստանդարտ', '00:15:05', '00:20:00'),
(7, 'Կես դրույք', '00:30:00', '01:00:00'),
(8, 'Հերթափող', '00:15:00', '00:20:00');

-- --------------------------------------------------------

--
-- Table structure for table `tourniquet`
--

CREATE TABLE IF NOT EXISTS `tourniquet` (
  `number` int(11) NOT NULL AUTO_INCREMENT,
  `type` tinyint(1) NOT NULL,
  PRIMARY KEY (`number`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=114745 ;

--
-- Dumping data for table `tourniquet`
--

INSERT INTO `tourniquet` (`number`, `type`) VALUES
(1, 0),
(2, 1);

-- --------------------------------------------------------

--
-- Table structure for table `tourniquet_transaction`
--

CREATE TABLE IF NOT EXISTS `tourniquet_transaction` (
  `date_time` datetime NOT NULL,
  `tourniquet_number` int(11) NOT NULL,
  `emp_number` varchar(20) NOT NULL,
  `id` int(11) NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`id`),
  KEY `tourniquet_id` (`tourniquet_number`,`emp_number`),
  KEY `emp_number` (`emp_number`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=29 ;

--
-- Dumping data for table `tourniquet_transaction`
--

INSERT INTO `tourniquet_transaction` (`date_time`, `tourniquet_number`, `emp_number`, `id`) VALUES
('2015-05-10 09:00:00', 1, '123', 17),
('2015-05-10 09:05:00', 1, '444', 18),
('2015-05-10 09:10:00', 1, '451', 19),
('2015-05-10 09:15:00', 1, '456', 20),
('2015-05-10 10:00:00', 1, '774', 21),
('2015-05-10 10:30:00', 1, '852', 22),
('2015-05-10 18:00:00', 2, '123', 23),
('2015-05-10 18:05:00', 2, '444', 24),
('2015-05-10 18:10:00', 2, '451', 25),
('2015-05-10 18:15:00', 2, '456', 26),
('2015-05-10 19:00:00', 2, '774', 27),
('2015-05-10 19:30:00', 2, '852', 28);

--
-- Constraints for dumped tables
--

--
-- Constraints for table `department`
--
ALTER TABLE `department`
  ADD CONSTRAINT `department_ibfk_2` FOREIGN KEY (`schedule_id`) REFERENCES `schedule` (`id`);

--
-- Constraints for table `dep_positions`
--
ALTER TABLE `dep_positions`
  ADD CONSTRAINT `dep_positions_ibfk_1` FOREIGN KEY (`department_id`) REFERENCES `department` (`id`),
  ADD CONSTRAINT `dep_positions_ibfk_2` FOREIGN KEY (`position_id`) REFERENCES `position` (`id`);

--
-- Constraints for table `employer`
--
ALTER TABLE `employer`
  ADD CONSTRAINT `employer_ibfk_1` FOREIGN KEY (`schedule_id`) REFERENCES `schedule` (`id`),
  ADD CONSTRAINT `employer_ibfk_2` FOREIGN KEY (`register_address_id`) REFERENCES `address` (`id`),
  ADD CONSTRAINT `employer_ibfk_3` FOREIGN KEY (`living_address_id`) REFERENCES `address` (`id`);

--
-- Constraints for table `employer_dep_positions`
--
ALTER TABLE `employer_dep_positions`
  ADD CONSTRAINT `employer_dep_positions_ibfk_2` FOREIGN KEY (`dep_positions_id`) REFERENCES `dep_positions` (`id`),
  ADD CONSTRAINT `employer_dep_positions_ibfk_1` FOREIGN KEY (`employer_id`) REFERENCES `employer` (`id`);

--
-- Constraints for table `employer_employer_ids`
--
ALTER TABLE `employer_employer_ids`
  ADD CONSTRAINT `employer_employer_ids_ibfk_1` FOREIGN KEY (`emp_number`) REFERENCES `employer_ids` (`emp_number`),
  ADD CONSTRAINT `employer_employer_ids_ibfk_2` FOREIGN KEY (`employer_id`) REFERENCES `employer` (`id`);

--
-- Constraints for table `employer_phone_number`
--
ALTER TABLE `employer_phone_number`
  ADD CONSTRAINT `employer_phone_number_ibfk_1` FOREIGN KEY (`employer_id`) REFERENCES `employer` (`id`);

--
-- Constraints for table `original_tourniquet_transaction`
--
ALTER TABLE `original_tourniquet_transaction`
  ADD CONSTRAINT `original_tourniquet_transaction_ibfk_1` FOREIGN KEY (`tourniquet_number`) REFERENCES `tourniquet` (`number`),
  ADD CONSTRAINT `original_tourniquet_transaction_ibfk_2` FOREIGN KEY (`emp_number`) REFERENCES `employer_ids` (`emp_number`);

--
-- Constraints for table `schedule`
--
ALTER TABLE `schedule`
  ADD CONSTRAINT `schedule_ibfk_1` FOREIGN KEY (`schedule_type_id`) REFERENCES `schedule_type` (`id`);

--
-- Constraints for table `tourniquet_transaction`
--
ALTER TABLE `tourniquet_transaction`
  ADD CONSTRAINT `tourniquet_transaction_ibfk_2` FOREIGN KEY (`emp_number`) REFERENCES `employer_ids` (`emp_number`),
  ADD CONSTRAINT `tourniquet_transaction_ibfk_3` FOREIGN KEY (`tourniquet_number`) REFERENCES `tourniquet` (`number`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
