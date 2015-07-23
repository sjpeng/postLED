#include <string>
#include <iostream>         // for the input/output
#include <stdlib.h>         // for the getenv call
#include <sys/sysinfo.h>    // for the system uptime call
#include <cgicc/Cgicc.h>    // the cgicc headers
#include <cgicc/CgiDefs.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include "LED.h"            // the LED class from Chapter 5 of the book
using namespace std;
using namespace cgicc;
 
int main(){
   Cgicc form;                                     // the CGI form object
   string flashPeriod, command, ledvalue;                    // default values
   int led;
   
   form_iterator it = form.getElement("led");
   ledvalue = it->getValue();
   led = atoi(ledvalue.c_str());
   LED *leds = new LED(led);                        // the LED object
	  
   bool isStatus = form.queryCheckbox("status");   // get the state of the status checkbox
   it = form.getElement("period");   // get the period text value
   if (it == form.getElements().end() || it->getValue()==""){
      flashPeriod = "100";                         // if it is invalid use 100
   }
   else { flashPeriod = it->getValue(); }          // otherwise use submitted value
   it = form.getElement("command");                // get the radio command chosen
   if (it == form.getElements().end() || it->getValue()==""){
      command = "off";                             // if it is invalid use "off"
   }
   else { command = it->getValue(); }              // otherwise use submitted value
   char *value = getenv("REMOTE_ADDR");            // The remote address CGI env. variable
 
   // Generate the form but use states that are set in the form that was submitted
   cout << HTTPHTMLHeader() << endl;               // Generate the HTML form using cgicc
   cout << html() << head() << title("EBB C++ Post LED Example") << head() << endl;
   cout << body() << h1("BeagleBone LED Controller") << endl;;
   cout << "<form action=\"/cgi-bin/postLED.cgi\" method=\"POST\">\n";
   cout << "<div>LED <select name=\"led\"><option>0</option><option>1</option><option>2</option><option>3</option></select> Status: <input type=\"radio\" name=\"command\" value=\"on\""
        << ( command=="on" ? "checked":"") << "/> On "; // is the command="on"?
   cout << "<input type=\"radio\" name=\"command\" value=\"off\""
        << ( command=="off" ? "checked":"") << "/> Off ";
   cout << "<input type=\"radio\" name=\"command\" value=\"flash\""
        << ( command=="flash" ? "checked":"") << "/> Flash ";
   cout << "<input type=\"checkbox\" name=\"status\" " << (isStatus ? "checked":"")
        << " /> Display Status </div>";
   cout << "<input type=\"submit\" value=\"Execute Command\" />";
   cout << "</div></form>";
 
   // Process the form data to trigger the LED state
   if (command=="on") leds->turnOn();                   // turn the LED on?
   else if (command=="off") leds->turnOff();            // off?
   else if (command=="flash") leds->flash(flashPeriod); // flash with the period above
   else cout << "<div> Invalid command! </div>";        // not possible at the moment
   // If the Display Status checkbox is checked then display the status now
   // this should happen after the command is set, otherwise it is old data
   if (isStatus){
      cout << "<div>";
      leds->outputState();
      cout << "</div>";
   }
   cout << "<div> The CGI REMOTE_ADDR environment variable is " << value << "</div>";
   cout << body() << html();
   return 0;
}