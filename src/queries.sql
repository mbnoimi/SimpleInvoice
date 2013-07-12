/**** TABLE ****/
SELECT
data.id,
data.title,
data.device,
data.description,
data.cost,
data.recived,
data.status,
data.note
FROM
data
ORDER BY
data.id DESC

/**** DEVICES ****/
SELECT DISTINCT
data.device
FROM
data
ORDER BY
data.id DESC

/**** STATUSES ****/
SELECT DISTINCT
data.status
FROM
data
ORDER BY
data.id DESC

/**** FILTERS ****/
SELECT
data.id,
data.title,
data.device,
data.description,
data.cost,
data.recived,
data.status,
data.note
FROM
data
WHERE
data.title LIKE "%1"
ORDER BY
data.id DESC

/**** ADD ****/
INSERT INTO "main"."data" ("title", "device", "description", "cost", "recived", "note", "model", "serial", "sent", "phone", "status") VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10', '%11')


/**** UPDATE ****/
SELECT
data.id,
data.title,
data.device,
data.cost,
data.description,
data.recived,
data.model,
data.note,
data.serial,
data.sent,
data.phone,
data.status
FROM
data
WHERE
data.id = 1
