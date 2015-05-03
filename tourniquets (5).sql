-- phpMyAdmin SQL Dump
-- version 4.0.10deb1
-- http://www.phpmyadmin.net
--
-- Хост: localhost
-- Время создания: Май 04 2015 г., 02:16
-- Версия сервера: 5.5.40-0ubuntu0.14.04.1
-- Версия PHP: 5.5.9-1ubuntu4.5

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- База данных: `tourniquets`
--

-- --------------------------------------------------------

--
-- Структура таблицы `address`
--

CREATE TABLE IF NOT EXISTS `address` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `country` varchar(45) DEFAULT NULL,
  `city` varchar(45) DEFAULT NULL,
  `street` varchar(45) DEFAULT NULL,
  `h_number` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=31 ;

--
-- Дамп данных таблицы `address`
--

INSERT INTO `address` (`id`, `country`, `city`, `street`, `h_number`) VALUES
(2, '11333', 'ֆղդբդֆբ', 'դֆբ', 'դբդֆբ'),
(3, 'դֆբդֆբ', 'դֆբդֆ', 'բդֆբ', 'դֆբսդֆբ'),
(5, 'aassdd', 'aassdd', 'aassdd', 'aassdd'),
(6, 'wwww', 'wwww', 'wwww', 'wwww'),
(9, 'jjj', 'jjjj', 'jjj', 'jjj'),
(11, 'rr', 'rr', 'rr', 'rr'),
(12, 'uu', 'uu', 'uu', 'uu'),
(13, 'hh', 'hh', 'hh', 'hh'),
(15, 'pp', 'ppp', 'ppp', 'pp'),
(16, 'MMM', 'MMM', 'MMM', 'MMM'),
(17, 'mmm', 'mmm', 'mmm', 'mmm'),
(18, 'lk;', 'kl;', 'kl;', 'kl;'),
(20, 'WWW', 'WWW', 'MMM', 'MMM'),
(21, 'qqq', 'qqq', 'qqq', 'qqq'),
(22, 'jjj', 'jj', 'jjjj', 'jjj'),
(23, 'hh', 'h', 'hh', 'hh'),
(24, '111', '1111', '11', '111'),
(26, '111', '111', '111', '111'),
(27, '222', '22', '22', '11'),
(28, ';;;;;;;;', ';;;;;;;;;', ';;;;;;;;;;;', ';;;;;;;;;;'),
(29, 'kkk', 'kk', 'kkk', 'kkk'),
(30, '11112', '1112', '1112', '11112');

-- --------------------------------------------------------

--
-- Структура таблицы `department`
--

CREATE TABLE IF NOT EXISTS `department` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(45) DEFAULT NULL,
  `manager_id` int(11) NOT NULL,
  `schedule_id` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `fk_department_employeer1_idx` (`manager_id`),
  KEY `fk_department_schedule1_idx` (`schedule_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=22 ;

--
-- Дамп данных таблицы `department`
--

INSERT INTO `department` (`id`, `name`, `manager_id`, `schedule_id`) VALUES
(1, 'yrrryyt0001', 4, 2),
(3, '444525', 4, 2),
(6, 'ttttt111', 3, 6),
(9, 'ppoo', 6, 2),
(10, 'New dep', 9, 3),
(11, 'ooo', 9, 2),
(12, 'qqqq', 6, 2),
(13, 'yyyy', 3, 3),
(15, 'qqwwee', 3, 3),
(17, 'tttt', 6, 2),
(18, 'tt7777', 4, 3),
(19, 'hjhjhj', 20, 6),
(20, 'I''m here', 4, 2),
(21, 'I hope to go', 4, 4);

-- --------------------------------------------------------

--
-- Структура таблицы `dep_positions`
--

CREATE TABLE IF NOT EXISTS `dep_positions` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `department_id` int(11) NOT NULL,
  `position_id` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `department_id` (`department_id`,`position_id`),
  KEY `fk_dep_positions_department1_idx` (`department_id`),
  KEY `fk_dep_positions_position1` (`position_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=137 ;

--
-- Дамп данных таблицы `dep_positions`
--

INSERT INTO `dep_positions` (`id`, `department_id`, `position_id`) VALUES
(116, 1, 1),
(122, 1, 2),
(120, 1, 3),
(124, 1, 4),
(125, 1, 5),
(126, 1, 6),
(127, 1, 7),
(128, 1, 8),
(129, 1, 9),
(136, 1, 12),
(97, 3, 1),
(117, 6, 1),
(119, 6, 8),
(98, 9, 3),
(112, 9, 8),
(113, 9, 9),
(130, 10, 3),
(131, 10, 7),
(132, 10, 9),
(115, 12, 3),
(135, 21, 3);

-- --------------------------------------------------------

--
-- Структура таблицы `employer`
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
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=28 ;

--
-- Дамп данных таблицы `employer`
--

INSERT INTO `employer` (`id`, `firstname`, `lastname`, `middlename`, `birth_date`, `passport_series`, `passport_number`, `given_date`, `given_from`, `gender`, `is_conscript`, `family_status`, `children_num`, `minor_children_num`, `register_address_id`, `living_address_id`, `schedule_id`) VALUES
(3, 'Hazaapet11', 'Tunanyan', 'Andraniki', '2015-04-30', 'AH', '55566667', '2015-04-05', '006', '0', 0, '0', 0, 0, 2, 3, 8),
(4, 'Lilit', 'Hovhannisyan', 'Mkrtichi11', '2015-01-01', 'AH', '7777777', '2003-02-02', '003', '1', 1, '0', 0, 0, 2, 3, 2),
(6, 'վցվվ11', 'ցվ', 'ցվցվցվ', '2000-01-05', 'ցվ', 'փձջփձջձջ', '2000-01-01', '003', '0', 1, '0', 0, 0, 2, 3, 7),
(7, 'յյկլ․', 'յկլ;յկլ;', 'յկլ;յկլ;', '2000-01-05', 'rr', 'rrr', '2000-01-01', '', '0', 0, '0', 0, 0, 2, 3, 1),
(9, 'dfg', 'dsfg', 'sdfg', '2000-01-01', 'fg', '345453454', '2000-01-01', '346', '0', 0, '0', 346, 346, 2, 3, 2),
(14, 'kl;', 'kl;jk;', 'jkl;jk;', '2000-01-05', 'kl', '6578678789', '2000-01-01', '003', '1', 1, '0', 0, 0, 2, 3, 1),
(17, 'jkl', 'hkl', 'hjkl', '2000-01-01', 'hk', 'hjkl', '2000-01-01', 'hjk', '0', 1, '0', 67, 79, 2, 3, 3),
(19, 'rtyt', 'yerty', 'ertye', '2000-01-01', 'et', 'erty', '2000-01-01', '', '1', 1, '0', 0, 0, 2, 3, 1),
(20, 'ttt12222', 'ttg', 'ttr', '2000-01-01', 'rt', 'rt', '2000-01-01', 'rth', '1', 0, '1', 45, 45, 11, 6, 2),
(21, '111//1111', '444', '114', '2000-01-01', '14', '14', '2000-01-01', '14', '-1', 1, '1', 3, 2, 11, 6, 2),
(22, 'rr', 'rrr', 'rrr222', '2000-01-01', 'rr', 'rr', '2000-01-01', 'rr', '1', 1, '1', 11, 10, 11, 6, 2),
(23, '1111', '11', '11', '2000-01-01', '11', '11', '2000-01-01', '11', '1', 0, '1', 11, 11, 11, 9, 2),
(24, '22111', '220011', '22', '2000-01-01', '22', '22', '2000-01-01', '22', '1', 0, '1', 22, 22, 11, 9, 2),
(25, '111', '11', '22', '2000-01-01', '22', '22', '2000-01-01', '22', '1', 0, '1', 222, 224, 12, 6, 2),
(26, '444', '444', '111', '2000-01-01', '11', '11', '2000-01-01', '00', '1', 0, '1', 114, 10114, 11, 9, 2),
(27, '424', '42', '42', '2000-01-01', '44', '427', '2000-01-01', '774', '0', 0, '1', 41274, 427, 11, 9, 2);

-- --------------------------------------------------------

--
-- Структура таблицы `employer_dep_positions`
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
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=45 ;

--
-- Дамп данных таблицы `employer_dep_positions`
--

INSERT INTO `employer_dep_positions` (`employer_id`, `dep_positions_id`, `from`, `to`, `id`) VALUES
(3, 101, '2015-04-28', '2015-04-28', 16),
(3, 97, '2015-04-28', '2015-04-28', 18),
(3, 98, '2015-04-28', '2015-04-28', 19),
(3, 101, '2015-04-28', '2015-04-28', 21),
(3, 97, '2015-04-28', '2015-04-29', 24),
(3, 101, '2015-04-29', '2015-04-29', 25),
(3, 98, '2015-04-29', '2015-04-29', 26),
(6, 101, '2015-04-29', '2015-04-29', 27),
(6, 97, '2015-04-29', '2015-04-30', 28),
(3, 113, '2015-04-29', '2015-04-29', 29),
(3, 109, '2015-04-29', '2015-04-30', 30),
(9, 109, '2015-04-29', '2015-05-02', 31),
(20, 97, '2015-04-29', NULL, 32),
(21, 97, '2015-04-29', NULL, 33),
(22, 97, '2015-04-29', NULL, 34),
(23, 116, '2015-04-29', NULL, 35),
(24, 116, '2015-04-29', NULL, 36),
(25, 116, '2015-04-29', NULL, 37),
(26, 97, '2015-04-29', NULL, 38),
(27, 116, '2015-04-29', '2015-04-29', 39),
(27, 97, '2015-04-29', NULL, 40),
(7, 116, '2015-04-29', NULL, 41),
(3, 112, '2015-04-30', NULL, 42),
(6, 122, '2015-04-30', NULL, 43),
(9, 97, '2015-05-02', NULL, 44);

-- --------------------------------------------------------

--
-- Структура таблицы `employer_employer_ids`
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
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=36 ;

--
-- Дамп данных таблицы `employer_employer_ids`
--

INSERT INTO `employer_employer_ids` (`employer_id`, `from`, `to`, `emp_number`, `id`) VALUES
(3, '2015-04-30', NULL, ',,,tttkkk', 23),
(3, '2015-04-30', '2015-5-2', '222222', 24),
(4, '2015-04-30', '2015-4-30', '111111', 25),
(4, '2015-04-30', '2015-5-1', '44555', 26),
(6, '2015-05-01', NULL, '111111', 27),
(9, '2015-05-01', NULL, 'hhhhhh111', 28),
(17, '2015-05-01', NULL, 'newEmployerId', 29),
(4, '2015-05-01', NULL, 'kiuu', 30),
(7, '2015-05-01', '2015-5-1', '111122222', 31),
(7, '2015-05-01', NULL, '1234567890', 32),
(3, '2015-05-02', '2015-5-2', '111122222', 33),
(20, '2015-05-02', NULL, '44555', 34),
(3, '2015-05-02', NULL, '8888', 35);

-- --------------------------------------------------------

--
-- Структура таблицы `employer_ids`
--

CREATE TABLE IF NOT EXISTS `employer_ids` (
  `emp_number` varchar(15) NOT NULL,
  `id_type` int(11) NOT NULL,
  PRIMARY KEY (`emp_number`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `employer_ids`
--

INSERT INTO `employer_ids` (`emp_number`, `id_type`) VALUES
(',,,tttkkk', 1),
('111111', 0),
('111122222', 0),
('1234567890', 1),
('222222', 0),
('44555', 0),
('8888', 0),
('hhhhhh111', 0),
('kiuu', 1),
('newEmployerId', 1),
('QQQQ', 0),
('TTT', 0),
('yyyyy', 0),
('yyyyyy', 0),
('zzzzz', 0);

-- --------------------------------------------------------

--
-- Структура таблицы `employer_phone_number`
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
-- Дамп данных таблицы `employer_phone_number`
--

INSERT INTO `employer_phone_number` (`employer_id`, `from`, `to`, `phone_number`) VALUES
(3, '2010-01-01', '2010-01-01', '+347777777711'),
(7, '2002-02-02', '2003-03-03', '+37455555'),
(3, '2097-08-02', '2015-04-20', '+37477441995'),
(17, '2090-02-02', '2002-02-02', '+37477531732'),
(3, '2002-02-02', '2003-03-03', '445551');

-- --------------------------------------------------------

--
-- Структура таблицы `original_tourniquet_transaction`
--

CREATE TABLE IF NOT EXISTS `original_tourniquet_transaction` (
  `date_time` datetime NOT NULL,
  `tourniquet_number` int(11) NOT NULL,
  `emp_number` varchar(20) NOT NULL,
  KEY `tourniquet_id` (`tourniquet_number`,`emp_number`),
  KEY `emp_number` (`emp_number`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `original_tourniquet_transaction`
--

INSERT INTO `original_tourniquet_transaction` (`date_time`, `tourniquet_number`, `emp_number`) VALUES
('2015-05-01 07:22:25', 211, '111111'),
('2014-03-12 09:21:28', 1, ',,,tttkkk'),
('2014-03-12 09:21:38', 1, '111111'),
('2014-03-12 09:21:42', 1, 'hhhhhh111'),
('2014-03-12 09:22:07', 1, '111111'),
('2014-03-12 09:24:01', 1, ',,,tttkkk'),
('2014-03-12 09:26:35', 1, '111111'),
('2014-03-12 09:27:05', 1, ',,,tttkkk'),
('2014-03-12 09:29:57', 1, 'hhhhhh111'),
('2014-03-12 09:21:28', 1, ',,,tttkkk'),
('2014-03-12 09:21:38', 1, '111111'),
('2014-03-12 09:21:42', 1, 'hhhhhh111'),
('2014-03-12 09:22:07', 1, '111111'),
('2014-03-12 09:24:01', 1, ',,,tttkkk'),
('2014-03-12 09:26:35', 1, '111111'),
('2014-03-12 09:27:05', 1, ',,,tttkkk'),
('2014-03-12 09:29:57', 1, 'hhhhhh111'),
('2014-03-12 09:21:28', 1, ',,,tttkkk'),
('2014-03-12 09:21:38', 1, '111111'),
('2014-03-12 09:21:42', 1, 'hhhhhh111'),
('2014-03-12 09:22:07', 1, '111111'),
('2014-03-12 09:24:01', 1, ',,,tttkkk'),
('2014-03-12 09:26:35', 1, '111111'),
('2014-03-12 09:27:05', 1, ',,,tttkkk'),
('2014-03-12 09:29:57', 1, 'hhhhhh111'),
('2014-03-12 09:21:28', 1, ',,,tttkkk'),
('2014-03-12 09:21:38', 1, '111111'),
('2014-03-12 09:21:42', 1, 'hhhhhh111'),
('2014-03-12 09:22:07', 1, '111111'),
('2014-03-12 09:24:01', 1, ',,,tttkkk'),
('2014-03-12 09:26:35', 1, '111111'),
('2014-03-12 09:27:05', 1, ',,,tttkkk'),
('2014-03-12 09:29:57', 1, 'hhhhhh111');

--
-- Триггеры `original_tourniquet_transaction`
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
-- Структура таблицы `position`
--

CREATE TABLE IF NOT EXISTS `position` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '	',
  `name` varchar(45) DEFAULT NULL,
  `schedule_id` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `fk_position_schedule1_idx` (`schedule_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=13 ;

--
-- Дамп данных таблицы `position`
--

INSERT INTO `position` (`id`, `name`, `schedule_id`) VALUES
(1, 'mfffm11', 1),
(2, '1244', 1),
(3, 'yyyyyy', 3),
(4, '112', 3),
(5, '', 1),
(6, 'oooo', 2),
(7, '77777', 2),
(8, 'iiiiiii', 3),
(9, 'PPPP', 4),
(12, '', 1);

-- --------------------------------------------------------

--
-- Структура таблицы `schedule`
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
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=10 ;

--
-- Дамп данных таблицы `schedule`
--

INSERT INTO `schedule` (`id`, `standart_in_time`, `standart_out_time`, `mon_in`, `mon_out`, `thsd_in`, `thsd_out`, `wed_in`, `wed_out`, `thrsd_in`, `thrsd_out`, `fri_in`, `fri_out`, `sat_in`, `sat_out`, `sun_in`, `sun_out`, `interval_in_days`, `schedule_type_id`) VALUES
(1, '15:00:00', '19:00:00', '15:00:00', '16:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', 2, 7),
(2, '09:00:00', '18:00:00', '15:00:00', '16:00:00', '04:06:00', '05:05:00', '04:03:00', '06:00:00', '05:00:00', '05:04:00', '09:04:00', '03:00:00', '03:06:00', '06:05:00', '03:07:00', '00:00:00', 4, 7),
(3, '08:05:00', '04:08:00', '02:05:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', 4, 7),
(4, '15:24:00', '16:15:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', 144, 3),
(6, '02:05:00', '05:06:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', 10, 3),
(7, '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', 4, 3),
(8, '03:03:00', '04:05:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', 0, 3),
(9, '03:05:00', '05:06:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '00:00:00', 41, 5);

-- --------------------------------------------------------

--
-- Структура таблицы `schedule_type`
--

CREATE TABLE IF NOT EXISTS `schedule_type` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(45) DEFAULT NULL,
  `allow_lag` time DEFAULT NULL,
  `ignore_time` time DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=8 ;

--
-- Дамп данных таблицы `schedule_type`
--

INSERT INTO `schedule_type` (`id`, `name`, `allow_lag`, `ignore_time`) VALUES
(3, '414147111', '02:05:05', '15:00:00'),
(5, '14447', '00:00:00', '00:00:00'),
(7, 'jjjjhhhyyy', '11:05:00', '04:07:00');

-- --------------------------------------------------------

--
-- Структура таблицы `tourniquet`
--

CREATE TABLE IF NOT EXISTS `tourniquet` (
  `number` int(11) NOT NULL AUTO_INCREMENT,
  `type` tinyint(1) NOT NULL,
  PRIMARY KEY (`number`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=114745 ;

--
-- Дамп данных таблицы `tourniquet`
--

INSERT INTO `tourniquet` (`number`, `type`) VALUES
(1, 1),
(211, 0),
(3444, 1),
(5543, 0),
(114744, 1);

-- --------------------------------------------------------

--
-- Структура таблицы `tourniquet_transaction`
--

CREATE TABLE IF NOT EXISTS `tourniquet_transaction` (
  `date_time` datetime NOT NULL,
  `tourniquet_number` int(11) NOT NULL,
  `emp_number` varchar(20) NOT NULL,
  `id` int(11) NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`id`),
  KEY `tourniquet_id` (`tourniquet_number`,`emp_number`),
  KEY `emp_number` (`emp_number`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=32 ;

--
-- Дамп данных таблицы `tourniquet_transaction`
--

INSERT INTO `tourniquet_transaction` (`date_time`, `tourniquet_number`, `emp_number`, `id`) VALUES
('2017-03-12 09:25:57', 3444, 'hhhhhh111', 6),
('2014-03-12 09:21:42', 1, 'hhhhhh111', 8),
('2014-03-12 09:22:07', 1, '111111', 9),
('2014-03-12 09:17:35', 211, '111111', 11),
('2014-03-12 09:29:57', 1, 'hhhhhh111', 12),
('2013-11-07 00:00:00', 211, '111111', 13),
('2000-01-01 00:00:00', 5543, '44555', 15),
('2014-03-12 09:21:28', 1, ',,,tttkkk', 16),
('2014-03-12 09:21:42', 211, 'hhhhhh111', 18),
('2014-03-12 09:22:07', 1, '111111', 19),
('2014-03-12 09:26:35', 1, '111111', 21),
('2014-03-12 09:27:05', 1, ',,,tttkkk', 22),
('2014-03-12 09:29:57', 1, 'hhhhhh111', 23),
('2014-03-12 09:21:38', 1, '111111', 25),
('2014-03-12 09:22:07', 1, '111111', 27),
('2014-03-12 09:24:01', 1, ',,,tttkkk', 28),
('2014-03-12 09:27:05', 1, ',,,tttkkk', 30),
('2014-03-12 09:29:57', 1, 'hhhhhh111', 31);

--
-- Ограничения внешнего ключа сохраненных таблиц
--

--
-- Ограничения внешнего ключа таблицы `department`
--
ALTER TABLE `department`
  ADD CONSTRAINT `department_ibfk_1` FOREIGN KEY (`manager_id`) REFERENCES `employer` (`id`),
  ADD CONSTRAINT `department_ibfk_2` FOREIGN KEY (`schedule_id`) REFERENCES `schedule` (`id`);

--
-- Ограничения внешнего ключа таблицы `dep_positions`
--
ALTER TABLE `dep_positions`
  ADD CONSTRAINT `dep_positions_ibfk_1` FOREIGN KEY (`department_id`) REFERENCES `department` (`id`),
  ADD CONSTRAINT `dep_positions_ibfk_2` FOREIGN KEY (`position_id`) REFERENCES `position` (`id`);

--
-- Ограничения внешнего ключа таблицы `employer`
--
ALTER TABLE `employer`
  ADD CONSTRAINT `employer_ibfk_1` FOREIGN KEY (`schedule_id`) REFERENCES `schedule` (`id`),
  ADD CONSTRAINT `employer_ibfk_2` FOREIGN KEY (`register_address_id`) REFERENCES `address` (`id`),
  ADD CONSTRAINT `employer_ibfk_3` FOREIGN KEY (`living_address_id`) REFERENCES `address` (`id`);

--
-- Ограничения внешнего ключа таблицы `employer_employer_ids`
--
ALTER TABLE `employer_employer_ids`
  ADD CONSTRAINT `employer_employer_ids_ibfk_1` FOREIGN KEY (`emp_number`) REFERENCES `employer_ids` (`emp_number`),
  ADD CONSTRAINT `employer_employer_ids_ibfk_2` FOREIGN KEY (`employer_id`) REFERENCES `employer` (`id`);

--
-- Ограничения внешнего ключа таблицы `employer_phone_number`
--
ALTER TABLE `employer_phone_number`
  ADD CONSTRAINT `employer_phone_number_ibfk_1` FOREIGN KEY (`employer_id`) REFERENCES `employer` (`id`);

--
-- Ограничения внешнего ключа таблицы `original_tourniquet_transaction`
--
ALTER TABLE `original_tourniquet_transaction`
  ADD CONSTRAINT `original_tourniquet_transaction_ibfk_2` FOREIGN KEY (`emp_number`) REFERENCES `employer_ids` (`emp_number`),
  ADD CONSTRAINT `original_tourniquet_transaction_ibfk_1` FOREIGN KEY (`tourniquet_number`) REFERENCES `tourniquet` (`number`);

--
-- Ограничения внешнего ключа таблицы `schedule`
--
ALTER TABLE `schedule`
  ADD CONSTRAINT `schedule_ibfk_1` FOREIGN KEY (`schedule_type_id`) REFERENCES `schedule_type` (`id`);

--
-- Ограничения внешнего ключа таблицы `tourniquet_transaction`
--
ALTER TABLE `tourniquet_transaction`
  ADD CONSTRAINT `tourniquet_transaction_ibfk_2` FOREIGN KEY (`emp_number`) REFERENCES `employer_ids` (`emp_number`),
  ADD CONSTRAINT `tourniquet_transaction_ibfk_3` FOREIGN KEY (`tourniquet_number`) REFERENCES `tourniquet` (`number`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
