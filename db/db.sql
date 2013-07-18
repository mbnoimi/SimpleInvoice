/*
Navicat SQLite Data Transfer

Source Server         : SQLite
Source Server Version : 30706
Source Host           : :0

Target Server Type    : SQLite
Target Server Version : 30706
File Encoding         : 65001

Date: 2013-07-13 01:23:20
*/

PRAGMA foreign_keys = OFF;

-- ----------------------------
-- Table structure for "_data_old_20130712"
-- ----------------------------
DROP TABLE "_data_old_20130712";
CREATE TABLE "_data_old_20130712" (
"id"  INTEGER NOT NULL,
"title"  TEXT NOT NULL,
"device"  TEXT,
"model"  TEXT,
"serial"  TEXT,
"recived"  TEXT,
"sent"  TEXT,
"phone"  TEXT,
"description"  TEXT,
"parts"  TEXT,
"note"  TEXT,
"status"  TEXT,
"cost"  TEXT,
PRIMARY KEY ("id" ASC),
UNIQUE ("id" ASC)
)

;

-- ----------------------------
-- Records of _data_old_20130712
-- ----------------------------
BEGIN;
INSERT INTO "_data_old_20130712" VALUES (1, 'Ahmadf', 'Sony', 'X8', 24464646, '10/10/2011', '10/20/2015', 464646464, 'sadkjfas dasdj aksgd fasgdg uiasgdfiuasgd', '1;654;6546', 'sdfa sdkfasdu fuyasdg ufiyagsdu adgf ugasd gasdg ugasudgfuyasgdgfasug uasgdugasudfsad
f asdfasdf ', 1, 354654);
INSERT INTO "_data_old_20130712" VALUES (2, 'Waleed', 'nokia', '55x', 4654, null, null, null, null, null, null, null, null);
COMMIT;

-- ----------------------------
-- Table structure for "_data_old_20130712_1"
-- ----------------------------
DROP TABLE "_data_old_20130712_1";
CREATE TABLE "_data_old_20130712_1" (
"id"  INTEGER NOT NULL,
"title"  TEXT NOT NULL,
"device"  TEXT,
"description"  TEXT,
"cost"  TEXT,
"note"  TEXT,
"recived"  TEXT,
"model"  TEXT,
"serial"  TEXT,
"sent"  TEXT,
"phone"  TEXT,
"status"  TEXT,
PRIMARY KEY ("id" ASC),
UNIQUE ("id" ASC)
)

;

-- ----------------------------
-- Records of _data_old_20130712_1
-- ----------------------------
BEGIN;
INSERT INTO "_data_old_20130712_1" VALUES (1, 'Ahamd Jassem', 'Sony', 'Battary', 700, 'none', '10/07/2013', 'x10', '6464-s524645', null, 91564544, 1);
INSERT INTO "_data_old_20130712_1" VALUES (2, 'Wael Najee', 'Nokia', 'Battary', 500, 'paied 100', '06/07/2013', 'x10-mini', '2546-s', null, 926464448, 0);
INSERT INTO "_data_old_20130712_1" VALUES (3, 'Mohammad Jassem', 'Nokia', 'Power', 100, null, '29/', null, null, null, null, null);
COMMIT;

-- ----------------------------
-- Table structure for "data"
-- ----------------------------
DROP TABLE "data";
CREATE TABLE "data" (
"id"  INTEGER NOT NULL,
"title"  TEXT NOT NULL,
"device"  TEXT,
"description"  TEXT,
"cost"  TEXT,
"recived"  TEXT,
"note"  TEXT,
"model"  TEXT,
"serial"  TEXT,
"sent"  TEXT,
"phone"  TEXT,
"status"  TEXT,
PRIMARY KEY ("id" ASC),
UNIQUE ("id" ASC)
)

;

-- ----------------------------
-- Records of data
-- ----------------------------
BEGIN;
INSERT INTO "data" VALUES (1, 'Ahamd Jassem', 'Sony', 'Battary', 700, '2013/06/29', 'none', 'x10', '6464-s524645', '', 91564544, 'Pending');
INSERT INTO "data" VALUES (2, 'Wael Najee', 'Nokia', 'Battary', 500, '2013/07/06', 'paied 100', 'x10-mini', '2546-s', null, 926464448, 'Pending');
INSERT INTO "data" VALUES (3, 'Mohammad Jassem', 'Nokia', 'Power', 100, '2013/07/10', null, null, null, null, null, 'Delivered');
INSERT INTO "data" VALUES (4, 'Ahamd', 'Nokia', 'des', 6, '2013/07/12', 'asdsdfasd', 'sx', 656488, '2000/01/01', 546464, 'Pending');
INSERT INTO "data" VALUES (5, 'Ahamd', 'Nokia', 'des', 6, '2013/07/12', 'asdsdfasd', 'sx', 656488, '2000/01/01', 546464, 'Pending');
INSERT INTO "data" VALUES (6, 'Wael', 'Sony', 'sdfsd fasdf', 9500, '2013/07/11', 'sdfs f', '', 464564, '2000/01/01', '', 'Pending');
INSERT INTO "data" VALUES (7, 'Isam', 'Sony', 'dfg', 19, '2013/07/01', '', 3131, 2341, '2000/01/01', 5354, 'Pending');
INSERT INTO "data" VALUES (8, 'Mohannad', 'Sony', '', 0, '2013/07/12', '', '', '', '2000/01/01', 1205, 'Pending');
INSERT INTO "data" VALUES (9, 'Mamdouh', 'hp', '', 7, '2013/07/12', '', '', '', '2000/01/01', '', 'Pending');
INSERT INTO "data" VALUES (10, 'Waheed Basha', 'hp', '', 11, '2013/05/06', '', '', '', '2000/01/01', 54654, 'Pending');
COMMIT;
