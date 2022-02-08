#ifndef MYMETRIC_CONSTANTS_H
#define MYMETRIC_CONSTANTS_H

const char MY_METRIC[] = "MyMetric";

const char HTTP[] = "http";
const char TCP[] = "tcp";

const char EMPTY[] = "";
const char TIME[] = "time";
const char STOCKS[] = "stocks";
const char WEATHER[] = "weather";
const char SETUP[] = "setup";
const char CYCLE[] = "cycle";
const char OFF[] = "off";

const char TIME_MODE_ACTIVE[] = "Time Mode Active";
const char WEATHER_MODE_ACTIVE[] = "Weather Mode Active";
const char STOCKS_MODE_ACTIVE[] = "Stocks Mode Active";
const char SETUP_MODE_ACTIVE[] = "Setup Mode Active";
const char CYCLE_MODE_ACTIVE[] = "Cycle Mode Active";
const char OFF_MODE_ACTIVE[] = "Screen Off Mode Active";

const char TEXT_HTML[] = "text/html";
const char TEXT_PLAIN[] = "text/plain";
const char APPLICATION_JSON[] = "application/json";

const char INITIALIZED[] = "initialized";
const char TEXT_COLOR[] = "text-color";
const char BACKGROUND_COLOR[] = "background-color";
const char BRIGHTNESS[] = "brightness";
const char CURRENT_MODE[] = "current-mode";
const char LOCATION[] = "location";
const char GMT_OFFSET[] = "gmt-offset";
const char DISPLAYED_STOCKS[] = "displayed-stocks";
const char STOCKS_SPEED[] = "stocks-speed";
const char CYCLE_SPEED[] = "cycle-speed";
const char CYCLE_MODES[] = "cycle-modes";
const char PLAIN[] = "plain";

const char LOCATION_HEADER[] = "Location";


const char PREFERENCES_MANAGER_PREFIX[] = "[Preferences Manager] ";
const char MY_METRIC_PREFIX[] = "[MyMetric] ";
const char FILE_MANAGER_PREFIX[] = "[File Manager] ";

static const char PAGE_UPLOAD[] PROGMEM = R"(
{
  "uri": "/upload",
  "title": "Upload",
  "menu": true,
  "element": [
    { "name":"caption", "type":"ACText", "value":"<h2>File uploading platform<h2>" },
    { "name":"upload_file", "type":"ACFile", "label":"Select file: ", "store":"fs" },
    { "name":"upload", "type":"ACSubmit", "value":"UPLOAD", "uri":"/upload" }
  ]
}
)";

// Upload result display
static const char PAGE_BROWSE[] PROGMEM = R"(
{
  "uri": "/uploadResult",
  "title": "Upload",
  "menu": false,
  "element": [
    { "name":"caption", "type":"ACText", "value":"<h2>Uploading ended<h2>" },
    { "name":"filename", "type":"ACText" },
    { "name":"size", "type":"ACText", "format":"%s bytes uploaded" },
    { "name":"content_type", "type":"ACText", "format":"Content: %s" }
  ]
}
)";

#endif //MYMETRIC_CONSTANTS_H
