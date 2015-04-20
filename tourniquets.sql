-- phpMyAdmin SQL Dump
-- version 4.0.10deb1
-- http://www.phpmyadmin.net
--
-- Хост: localhost
-- Время создания: Апр 20 2015 г., 14:29
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
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

--
-- Дамп данных таблицы `address`
--

INSERT INTO `address` (`id`, `country`, `city`, `street`, `h_number`) VALUES
(1, 'Armenia', 'Erevan', 'May 9', '8/28');

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
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

--
-- Дамп данных таблицы `department`
--

INSERT INTO `department` (`id`, `name`, `manager_id`, `schedule_id`) VALUES
(1, 'yrrryyt', 3, 2),
(2, 'rtyyttt', 1, 1);

-- --------------------------------------------------------

--
-- Структура таблицы `dep_positions`
--

CREATE TABLE IF NOT EXISTS `dep_positions` (
  `id` int(11) NOT NULL,
  `department_id` int(11) NOT NULL,
  `position_id` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `fk_dep_positions_department1_idx` (`department_id`),
  KEY `fk_dep_positions_position1` (`position_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Структура таблицы `employer`
--

CREATE TABLE IF NOT EXISTS `employer` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `firstname` varchar(45) DEFAULT NULL,
  `lastname` varchar(45) DEFAULT NULL,
  `middlename` varchar(45) DEFAULT NULL,
  `bidth_date` datetime DEFAULT NULL,
  `passport_series` varchar(2) DEFAULT NULL,
  `passport_number` varchar(10) DEFAULT NULL,
  `given_date` datetime DEFAULT NULL,
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
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=4 ;

--
-- Дамп данных таблицы `employer`
--

INSERT INTO `employer` (`id`, `firstname`, `lastname`, `middlename`, `bidth_date`, `passport_series`, `passport_number`, `given_date`, `given_from`, `gender`, `is_conscript`, `family_status`, `children_num`, `minor_children_num`, `register_address_id`, `living_address_id`, `schedule_id`) VALUES
(1, 'Andranik', 'Hovhannisyan', NULL, '2015-04-02 00:00:00', 'AH', '44455544', '2015-04-13 00:00:00', '003', '1', NULL, NULL, NULL, NULL, 0, 0, 0),
(2, 'Andranik', 'Hovhannisyan', NULL, '2015-04-02 00:00:00', 'AH', '4444455', '2015-04-05 00:00:00', '003', '1', NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(3, 'Hazaapet', 'Tunanyan', NULL, '2015-04-30 00:00:00', 'AH', '55566667', '2015-04-05 00:00:00', '006', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

-- --------------------------------------------------------

--
-- Структура таблицы `employer_dep_positions`
--

CREATE TABLE IF NOT EXISTS `employer_dep_positions` (
  `employer_id` int(11) NOT NULL,
  `dep_positions_id` int(11) NOT NULL,
  `from` date DEFAULT NULL,
  `to` date DEFAULT NULL,
  PRIMARY KEY (`employer_id`,`dep_positions_id`),
  KEY `fk_employer_has_dep_positions_dep_positions1_idx` (`dep_positions_id`),
  KEY `fk_employer_has_dep_positions_employer1_idx` (`employer_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Структура таблицы `employer_employer_ids`
--

CREATE TABLE IF NOT EXISTS `employer_employer_ids` (
  `employer_id` int(11) NOT NULL,
  `from` date DEFAULT NULL,
  `to` varchar(45) DEFAULT NULL,
  `employer_ids_emp_number` varchar(15) NOT NULL,
  PRIMARY KEY (`employer_id`,`employer_ids_emp_number`),
  KEY `fk_employer_ids_has_employer_employer1_idx` (`employer_id`),
  KEY `fk_employer_employer_ids_employer_ids1_idx` (`employer_ids_emp_number`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

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
('kiuu', 0);

-- --------------------------------------------------------

--
-- Структура таблицы `employer_phone_number`
--

CREATE TABLE IF NOT EXISTS `employer_phone_number` (
  `employer_id` int(11) NOT NULL,
  `from` date DEFAULT NULL,
  `to` date DEFAULT NULL,
  `phone_number` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`employer_id`),
  KEY `fk_phone_number_has_employer_employer1_idx` (`employer_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

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
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

--
-- Дамп данных таблицы `position`
--

INSERT INTO `position` (`id`, `name`, `schedule_id`) VALUES
(1, 'mfffm', 1);

-- --------------------------------------------------------

--
-- Структура таблицы `schedule`
--

CREATE TABLE IF NOT EXISTS `schedule` (
  `id` int(11) NOT NULL,
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
  `interval_in_dates` int(11) DEFAULT NULL,
  `schedule_type_id` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `fk_schedule_schedule_type1_idx` (`schedule_type_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `schedule`
--

INSERT INTO `schedule` (`id`, `standart_in_time`, `standart_out_time`, `mon_in`, `mon_out`, `thsd_in`, `thsd_out`, `wed_in`, `wed_out`, `thrsd_in`, `thrsd_out`, `fri_in`, `fri_out`, `sat_in`, `sat_out`, `sun_in`, `sun_out`, `interval_in_dates`, `schedule_type_id`) VALUES
(1, '15:00:00', '19:00:00', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0),
(2, '09:00:00', '18:00:00', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0);

-- --------------------------------------------------------

--
-- Структура таблицы `schedule_type`
--

CREATE TABLE IF NOT EXISTS `schedule_type` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(45) DEFAULT NULL,
  `schedule_info_id` int(11) NOT NULL,
  `allow_lag` int(11) DEFAULT NULL,
  `ignore time` time DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Структура таблицы `turnicet`
--

CREATE TABLE IF NOT EXISTS `turnicet` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `number` varchar(10) DEFAULT NULL,
  `type` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `in_number_UNIQUE` (`number`),
  UNIQUE KEY `out_number_UNIQUE` (`type`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
