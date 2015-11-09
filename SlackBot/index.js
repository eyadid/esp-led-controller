var request = require("request");
var Bot = require('slackbots');

// create a bot

var LEDIP = '<IP OF SIGN>';

var settings = {
    token: '<BOT TOKEN - See http://###.slack.com/services/new/bot>',
    name: '<Name of Bot>'
};
var bot = new Bot(settings);

bot.on('message', function(message) {
	if(message.type === "message" && message.text){
		request('http://' + LEDIP + '/led/clear', function (error, response, body) {
   			if (!error && response.statusCode == 200) {
				request('http://' + LEDIP + '/led/print?text=' + message.text, function (error, response, body) {});
			}
		});
	}
});


