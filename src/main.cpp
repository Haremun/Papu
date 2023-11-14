#include "ESP8266WiFi.h"
#include "ESP8266WebServer.h"

ESP8266WebServer server(80);

void handleRootPath();

const char *htmlMessage = "<!DOCTYPE html><html><head>    <link rel=\"preconnect\" href=\"https://fonts.googleapis.com\">    <link rel=\"preconnect\" href=\"https://fonts.gstatic.com\" crossorigin>    <link href=\"https://fonts.googleapis.com/css2?family=Agbalumo&display=swap\" rel=\"stylesheet\">    <link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.4.2/css/all.min.css\"></head><style>    body {        font-family: Agbalumo;    }    .menu {        display: flex;        justify-content: space-between;        max-width: 80%;        margin: auto;        margin-bottom: 40px;    }    .item {        display: flex;        flex-direction: column;        align-items: center;    }    .item :hover {        cursor: pointer;    }    .item span {        font-size: 1.6em;    }    span {        color: #6096B4;    }    .card {        margin: 8px 15px;        border-radius: 6px;        display: flex;        justify-content: space-between;        padding: 25px 15px;        font-size: 3em;    }    .line {        width: 90%;        height: 2px;        background: #EEE9DA;        margin: auto;    }</style><script>    function onClick(type) {        var date = new Date();        var data = localStorage.getItem('data') ?? \"\";        data += `${type},${date.getTime()};`;        localStorage.setItem('data', data);        var dateFormatted = `${pad(date.getHours())}:${pad(date.getMinutes())} ${pad(date.getDate())}.${pad(date.getMonth() + 1)}`;        addItem(type, dateFormatted);        setLastPapu();    }    function addItem(type, date) {        const menu = document.getElementById('items');        const div = document.createElement('div');        div.classList.add('card');        const spanType = document.createElement('span');        spanType.textContent = type;        div.appendChild(spanType);        const spanDate = document.createElement('span');        spanDate.textContent = date;        div.appendChild(spanDate);        const line = document.createElement('div');        line.classList.add('line');        menu.insertBefore(line, menu.firstChild);        menu.insertBefore(div, menu.firstChild);    }    function setLastPapu() {        var data = localStorage.getItem('data');        if (!data) return;        const rows = data.split(';');        lastRow = rows.findLast(el => el.indexOf('Papu start') !== -1);        var date = new Date(parseInt(lastRow.split(',')[1]));        const last = document.getElementById('last-papu');        last.textContent = `${pad(date.getHours())}:${pad(date.getMinutes())} ${pad(date.getDate())}.${pad(date.getMonth() + 1)}`;    }    function getData() {        var data = localStorage.getItem('data');        if (!data) return;        const rows = data.split(';');        rows.forEach(row => {            if (!row) return;            var date = new Date(parseInt(row.split(',')[1]));            var dateFormatted = `${pad(date.getHours())}:${pad(date.getMinutes())} ${pad(date.getDate())}.${pad(date.getMonth() + 1)}`;            addItem(row.split(',')[0], dateFormatted);        })    }    function pad(num) { return ('00' + num).substr(-2); }    window.onload = () => {        getData();        setLastPapu();    }</script><body>    <h1 style=\"text-align: center; font-size: 7em; color: #93BFCF;\">        Papu timer    </h1>    <div class=\"menu\" id=\"menu\">        <div class=\"item\" onclick=\"onClick('Papu start')\">            <i class=\"fa-solid fa-circle-plus\" style=\"color: #6096B4; font-size: 7em;\"></i>            <span>Papu start</span>        </div>        <div class=\"item\" onclick=\"onClick('Papu stop')\">            <i class=\"fa-solid fa-circle-plus\" style=\"color: #BDCDD6; font-size: 7em;\"></i>            <span>Papu stop</span>        </div>        <div class=\"item\" onclick=\"onClick('Spanko start')\">            <i class=\"fa-solid fa-circle-plus\" style=\"color: #6096B4; font-size: 7em;\"></i>            <span>Spanko start</span>        </div>        <div class=\"item\" onclick=\"onClick('Spanko stop')\">            <i class=\"fa-solid fa-circle-plus\" style=\"color: #BDCDD6; font-size: 7em;\"></i>            <span>Spanko stop</span>        </div>    </div>    <div style=\"height: 350px; width: 95%; margin: auto; overflow: hidden; border-radius: 45px; position: relative;\">        <div            style=\"position: absolute; z-index: 2; display: flex; flex-direction: column; justify-content: center; height: 100%; padding-left: 15px;\">            <span style=\"font-size: 4em; color: #EEE9DA;\">Ostanie Papu:</span>            <span style=\"font-size: 4em; color: #EEE9DA;\" id=\"last-papu\"></span>        </div>        <div style=\"position: absolute; z-index: 1; background: #222; width: 100%; height: 100%; opacity: 0.35;\">        </div>        <img style=\"margin-top: -250px; opacity: 1\"            src=\"https://drive.google.com/uc?export=view&id=1Gmcv4NeZOFyKwmFHJq_67TyPeWJ8uNqP\">    </div>    <div id=\"items\">    </div></body></html>";

int addr = 0;

void setup()
{
  Serial.begin(115200);
  WiFi.begin("x", "x"); // Connect to the WiFi network

  while (WiFi.status() != WL_CONNECTED)
  { // Wait for connection

    delay(500);
    Serial.println("Waiting to connect…");
  }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); // Print the local IP

  server.on("/", handleRootPath); // Associate the handler function to the path
  server.begin(); // Start the server
}

void loop()
{
  server.handleClient(); // Handling of incoming requests
}

void handleRootPath()
{ // Handler for the rooth path
  server.send(200, "text/html", htmlMessage);
}