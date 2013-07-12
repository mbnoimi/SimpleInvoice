/*
Navicat SQLite Data Transfer

Source Server         : SQLite
Source Server Version : 30706
Source Host           : :0

Target Server Type    : SQLite
Target Server Version : 30706
File Encoding         : 65001

Date: 2013-07-12 15:05:56
*/

PRAGMA foreign_keys = OFF;

-- ----------------------------
-- Table structure for "data"
-- ----------------------------
DROP TABLE "data";
CREATE TABLE "data" (
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
-- Records of data
-- ----------------------------
BEGIN;
INSERT INTO "data" VALUES (1, 'Ahmadf', 'Sony', 'X8', 24464646, '10/10/2011', '10/20/2015', 464646464, 'sadkjfas dasdj aksgd fasgdg uiasgdfiuasgd', '1;654;6546', 'sdfa sdkfasdu fuyasdg ufiyagsdu adgf ugasd gasdg ugasudgfuyasgdgfasug uasgdugasudfsad
f asdfasdf ', 1, 354654);
INSERT INTO "data" VALUES (2, 'Waleed', 'nokia', '55x', 4654, null, null, null, null, null, null, null, null);
COMMIT;
