// $Id$

/**
 * This file is part of Timescape developed by Wolf Maul and Semandra Inc. 
 * 2014-15 - http://semandra.com.
 * 
 * Timescape is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Timescape is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Timescape.  If not, see <http://www.gnu.org/licenses/>.
*/

var tl;

function Timescape_onLoad(XML_source, target_id) {
  var theme = Timeline.ClassicTheme.create(); // alter the defaults of the custom theme
  theme.event.bubble.width = 450;   // modify it
  theme.event.bubble.height = 400;
  theme.event.track.height = 30;
  theme.event.track.gap = 5;
  theme.event.tape.height = 8;
  theme.event.duration.impreciseOpacity = 100;
  theme.event.instant.impreciseOpacity = 100;

  var eventSource = new Timeline.DefaultEventSource();
  var d = Timeline.DateTime.parseGregorianDateTime("2015");


  var bandInfos = [
 
  
  // Main timeline band where data points are presented in detail
    Timeline.createBandInfo({
      width:          "90%",  //Sets the height of the display band relative to the size of the box height
      eventSource:    eventSource,
      intervalUnit:   Timeline.DateTime.YEAR, 
      intervalPixels: 100,
	  trackHeight: 900,
	  date:           d,
	  theme:          theme, // Apply the theme variables as set above for data points
      timeZone:       3
    }),
	// Secondary timeline showing a broader overview of datapoints
    Timeline.createBandInfo({
      overview:       true,
      width:          "10%", 
      eventSource:    eventSource,
	  date:           d,
      intervalUnit:   Timeline.DateTime.DECADE, 
      intervalPixels: 50
    })
  ];
  bandInfos[1].syncWith = 0;
  bandInfos[1].highlight = true;
  tl = Timeline.create(document.getElementById(target_id), bandInfos);
 Timeline.loadXML(XML_source, function(xml, url) { eventSource.loadXML(xml, url); }); // Original
 // Timeline.loadJSON(XML_source, function(xml, url) { eventSource.loadJSON(xml, url); }); //Semandra - parse JSON data instead of XML 
  

}
