-- MySQL dump 10.13  Distrib 5.5.40, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: tourniquets
-- ------------------------------------------------------
-- Server version	5.5.40-0ubuntu0.14.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `address`
--

DROP TABLE IF EXISTS `address`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `address` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `country` varchar(45) DEFAULT NULL,
  `city` varchar(45) DEFAULT NULL,
  `street` varchar(45) DEFAULT NULL,
  `h_number` char(10) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=888902 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `address`
--

LOCK TABLES `address` WRITE;
/*!40000 ALTER TABLE `address` DISABLE KEYS */;
INSERT INTO `address` VALUES (24,'sx2222','dssd11','sd','s'),(25,'Armenia','Erevan','May 9','8'),(26,'ggg','gggg','gg','g'),(27,'jjgggg','jj','jj','j'),(28,'hhh','hhh','hhh','h'),(29,'hhh','hhh','hh','h'),(30,'Armenia','Erevandd','May 9','8'),(31,'Armenia','Erevandd','May 9','8'),(32,'sx','dssd','sd','s'),(33,'Armenia','Erevan','May 9','8'),(34,'Armenia11','Erevandd11','May 911','811'),(35,'qqqq','qqq99999','99999',NULL),(888888,'777777','666666','555555',NULL),(888889,'44','444','4444','4'),(888890,'1','2','3','4'),(888891,'44','444','4444','4'),(888892,'111','222','333','4'),(888893,'111','222','333','4'),(888894,'111','222','333','4'),(888895,'111','222','333','4444'),(888896,'qqq11','1','qqq1','qqq11'),(888897,'oo','oo','oo','oo'),(888898,'iiii11','iii11','iii11','iii11'),(888899,'4444444','4444444','44444444444','44444444'),(888900,'a','7444a','547a','757a'),(888901,'hgh','gh','gh','ghhhhhh');
/*!40000 ALTER TABLE `address` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `dep_positions`
--

DROP TABLE IF EXISTS `dep_positions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `dep_positions` (
  `department_id` int(11) NOT NULL,
  `position_id` int(11) NOT NULL,
  PRIMARY KEY (`position_id`,`department_id`),
  KEY `fk_dep_positions_department1_idx` (`department_id`),
  CONSTRAINT `fk_dep_positions_department1` FOREIGN KEY (`department_id`) REFERENCES `department` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_dep_positions_position1` FOREIGN KEY (`position_id`) REFERENCES `position` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `dep_positions`
--

LOCK TABLES `dep_positions` WRITE;
/*!40000 ALTER TABLE `dep_positions` DISABLE KEYS */;
/*!40000 ALTER TABLE `dep_positions` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `department`
--

DROP TABLE IF EXISTS `department`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `department` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(45) DEFAULT NULL,
  `manager_id` int(11) NOT NULL,
  `schedule_id` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `fk_department_employeer1_idx` (`manager_id`),
  KEY `fk_department_schedule1_idx` (`schedule_id`),
  CONSTRAINT `fk_department_employeer1` FOREIGN KEY (`manager_id`) REFERENCES `employer` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_department_schedule1` FOREIGN KEY (`schedule_id`) REFERENCES `schedule` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `department`
--

LOCK TABLES `department` WRITE;
/*!40000 ALTER TABLE `department` DISABLE KEYS */;
INSERT INTO `department` VALUES (1,'daprt N2',15,2),(2,'sssss',1,1);
/*!40000 ALTER TABLE `department` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `employer`
--

DROP TABLE IF EXISTS `employer`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `employer` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `firstname` varchar(45) DEFAULT NULL,
  `lastname` varchar(45) DEFAULT NULL,
  `middlename` varchar(45) DEFAULT NULL,
  `birth_date` datetime DEFAULT NULL,
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
  `department_id` int(11) DEFAULT NULL,
  `position_id` int(11) DEFAULT NULL,
  `schedule_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `fk_employeer_address1_idx` (`register_address_id`),
  KEY `fk_employeer_address2_idx` (`living_address_id`),
  KEY `fk_employeer_Department1_idx` (`department_id`),
  KEY `fk_employeer_position1_idx` (`position_id`),
  KEY `fk_employeer_schedule1_idx` (`schedule_id`),
  CONSTRAINT `fk_employeer_address1` FOREIGN KEY (`register_address_id`) REFERENCES `address` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_employeer_address2` FOREIGN KEY (`living_address_id`) REFERENCES `address` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_employeer_Department1` FOREIGN KEY (`department_id`) REFERENCES `department` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_employeer_position1` FOREIGN KEY (`position_id`) REFERENCES `position` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_employeer_schedule1` FOREIGN KEY (`schedule_id`) REFERENCES `schedule` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=16 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `employer`
--

LOCK TABLES `employer` WRITE;
/*!40000 ALTER TABLE `employer` DISABLE KEYS */;
INSERT INTO `employer` VALUES (1,'first1111','qqq22','qqq','2015-03-06 00:00:00','q','qa','2015-03-27 00:00:00','qa','0',0,'0',14,14,35,24,NULL,NULL,NULL),(5,'Andranik','Hovhannisyan','Mkrtichi','2000-01-01 00:00:00','AH','123456789','2000-01-01 00:00:00','006','0',1,'0',56,9,24,24,NULL,NULL,NULL),(8,'Andranik','Hovhannisyan','Mkrtichi','2000-01-01 00:00:00','AH','123456789','2000-01-01 00:00:00','006','0',1,'0',56,9,24,24,NULL,NULL,NULL),(9,'yui','tyui','tyui','2015-03-06 00:00:00','yu','yui','2015-03-26 00:00:00','tyi','0',1,'0',41,40,888892,34,NULL,NULL,NULL),(11,'fsdg','sfdg','dsfg','2000-01-01 00:00:00','sd','sdfg','2000-01-01 00:00:00','sdf','0',1,'0',78,78,24,24,NULL,NULL,NULL),(12,'Andranik111','Hovhannisyan','Mkrtichi','2000-01-01 00:00:00','AH','123456789','2000-01-01 00:00:00','006','0',1,'0',56,9,24,24,NULL,NULL,NULL),(13,'','','','2015-03-06 00:00:00','','','2015-03-27 00:00:00','','0',0,'0',0,0,24,24,NULL,NULL,NULL),(14,'12a','12a','12a','2015-03-06 00:00:00','42','42','2015-03-27 00:00:00','42','0',1,'1',222,444,32,888898,NULL,NULL,NULL),(15,'df1','df1','df1','2000-01-01 00:00:00','df','df','2000-01-01 00:00:00','df','0',1,'1',89,78,24,24,NULL,NULL,NULL);
/*!40000 ALTER TABLE `employer` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `employer_ids`
--

DROP TABLE IF EXISTS `employer_ids`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `employer_ids` (
  `emp_number` int(11) NOT NULL,
  `employeer_id` int(11) DEFAULT NULL,
  `id_type` int(11) NOT NULL,
  PRIMARY KEY (`emp_number`),
  KEY `fk_employeer_ids_employeer_idx` (`employeer_id`),
  CONSTRAINT `fk_employeer_ids_employeer` FOREIGN KEY (`employeer_id`) REFERENCES `employer` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `employer_ids`
--

LOCK TABLES `employer_ids` WRITE;
/*!40000 ALTER TABLE `employer_ids` DISABLE KEYS */;
INSERT INTO `employer_ids` VALUES (0,1,0),(887,5,1),(1144,5,0),(1222,1,1),(1234,5,1),(2121,1,1),(6667,1,0),(7889,1,1),(11145,1,0),(23111,5,1),(55511,5,0),(114477,1,0),(667766,5,1);
/*!40000 ALTER TABLE `employer_ids` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `phone_number`
--

DROP TABLE IF EXISTS `phone_number`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `phone_number` (
  `number` varchar(25) NOT NULL,
  `employeer_id` int(11) NOT NULL,
  PRIMARY KEY (`number`),
  KEY `fk_phone_number_employeer1_idx` (`employeer_id`),
  CONSTRAINT `fk_phone_number_employeer1` FOREIGN KEY (`employeer_id`) REFERENCES `employer` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `phone_number`
--

LOCK TABLES `phone_number` WRITE;
/*!40000 ALTER TABLE `phone_number` DISABLE KEYS */;
INSERT INTO `phone_number` VALUES ('+37477441995',5),('+374558866',11),('444111',12);
/*!40000 ALTER TABLE `phone_number` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `position`
--

DROP TABLE IF EXISTS `position`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `position` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '	',
  `name` varchar(45) DEFAULT NULL,
  `schedule_id` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `fk_position_schedule1_idx` (`schedule_id`),
  CONSTRAINT `fk_position_schedule1` FOREIGN KEY (`schedule_id`) REFERENCES `schedule` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `position`
--

LOCK TABLES `position` WRITE;
/*!40000 ALTER TABLE `position` DISABLE KEYS */;
INSERT INTO `position` VALUES (1,'ddsdf',1),(2,'pashton',2);
/*!40000 ALTER TABLE `position` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `schedule`
--

DROP TABLE IF EXISTS `schedule`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `schedule` (
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
  KEY `fk_schedule_schedule_type1_idx` (`schedule_type_id`),
  CONSTRAINT `fk_schedule_schedule_type1` FOREIGN KEY (`schedule_type_id`) REFERENCES `schedule_type` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `schedule`
--

LOCK TABLES `schedule` WRITE;
/*!40000 ALTER TABLE `schedule` DISABLE KEYS */;
INSERT INTO `schedule` VALUES (1,'09:00:00','18:00:00',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,1),(2,'09:15:00','18:00:00',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,1);
/*!40000 ALTER TABLE `schedule` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `schedule_type`
--

DROP TABLE IF EXISTS `schedule_type`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `schedule_type` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(45) DEFAULT NULL,
  `allow_lag` int(11) DEFAULT NULL,
  `ignore time` time DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `schedule_type`
--

LOCK TABLES `schedule_type` WRITE;
/*!40000 ALTER TABLE `schedule_type` DISABLE KEYS */;
INSERT INTO `schedule_type` VALUES (1,'Standart',15,'00:00:15');
/*!40000 ALTER TABLE `schedule_type` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tourniquet`
--

DROP TABLE IF EXISTS `tourniquet`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tourniquet` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `number` varchar(10) DEFAULT NULL,
  `type` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `in_number_UNIQUE` (`number`),
  UNIQUE KEY `out_number_UNIQUE` (`type`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tourniquet`
--

LOCK TABLES `tourniquet` WRITE;
/*!40000 ALTER TABLE `tourniquet` DISABLE KEYS */;
/*!40000 ALTER TABLE `tourniquet` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `transaction`
--

DROP TABLE IF EXISTS `transaction`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `transaction` (
  `in_out` tinyint(1) NOT NULL,
  `date` datetime DEFAULT NULL,
  `turnicet_id` int(11) NOT NULL,
  `employeer_id` int(11) NOT NULL,
  PRIMARY KEY (`in_out`),
  KEY `fk_transaction_turnicet1_idx` (`turnicet_id`),
  KEY `fk_transaction_employeer_ids1_idx` (`employeer_id`),
  CONSTRAINT `fk_transaction_employeer_ids1` FOREIGN KEY (`employeer_id`) REFERENCES `employer_ids` (`emp_number`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_transaction_turnicet1` FOREIGN KEY (`turnicet_id`) REFERENCES `tourniquet` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transaction`
--

LOCK TABLES `transaction` WRITE;
/*!40000 ALTER TABLE `transaction` DISABLE KEYS */;
/*!40000 ALTER TABLE `transaction` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2015-03-19  7:28:12
