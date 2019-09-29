const functions = require('firebase-functions');
const admin = require('firebase-admin');
var moment = require('moment');

admin.initializeApp();

exports.saveStatus = functions.https.onRequest((req, res) => {
	try {
		if (req.query !== undefined && req.query !== "") {
			const status = req.query.status;

			moment.locale('IN');
			var currentTime = moment().utcOffset("+05:30").format("DD-MM-YYYY hh:mm:ss A");
			admin.database().ref("MainDoor/").push().set({
				"date": currentTime,
				"status": status
			});

			payload = {
				data: {
					"body": currentTime,
					"title": "Main-Door is " + status
				}
			};

			admin.messaging().sendToTopic("weather", payload);
			return res.status(200).send("Success");
		} else {
			return res.status(404).send("no parameter defined");
		}
	} catch (error) {
		return res.status(404).send(error.message);
	}
});