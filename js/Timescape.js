// $Id$

/**
 * This file is part of Timescape developed by Wolf Maul and Semandra Inc. 
 * 2014-17 - http://semandra.com.
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
  //var theme = Timeline.ClassicTheme.create(); // alter the defaults of the custom theme
  //theme.event.bubble.width = 450;   // modify it
  //theme.event.bubble.height = 400;
  //theme.event.track.height = 30;
  //theme.event.track.gap = 5;
  //theme.event.tape.height = 8;
  //theme.event.duration.impreciseOpacity = 100;
  //theme.event.instant.impreciseOpacity = 100;

  var eventSource = new Timeline.DefaultEventSource();
  //var d = Timeline.DateTime.parseGregorianDateTime("2015"); // Depreciated -- now set in admin


 /**/ var bandInfos = [
  // Main timeline band where data points are presented in detail
    Timeline.createBandInfo({
      width:          tsPrmWdth + "%",  //Sets the height of the display band relative to the size of the box height
      eventSource:    eventSource,
      intervalUnit:   tsPrmIntvl, //Timeline.DateTime.YEAR, 
      intervalPixels: 100,
	  trackHeight: 900,
	  direction: tsDirction,
	  date:           d,
	  theme:          theme, // Apply the theme variables as set above for data points
      timeZone:       3
    }),
	// Secondary timeline showing a broader overview of datapoints
    Timeline.createBandInfo({
      overview:       true,
      width:          tsSecWdth + "%", 
      eventSource:    eventSource,
	  date:           d,
      intervalUnit:   tsScndIntvl, 
      intervalPixels: 50
    })
  ];
  //console.log ("WHATS THIS: " + Timeline.FORWARD);
   console.log (Timeline.DateTime);
  bandInfos[1].syncWith = 0;
  bandInfos[1].highlight = true;
  tl = Timeline.create(document.getElementById(target_id), bandInfos);  
  //Timeline.loadXML(XML_source, function(xml, url) { eventSource.loadXML(xml, url); }); // Original
  Timeline.loadJSON(XML_source, function(json, url) { 
  		eventSource.loadJSON(json, url); 
	}); //Semandra - parse JSON data instead of XML 
  
	// Could more than one source be joined together before the rendering of the timeline?
	// Files would need to be in the same format -- database items and uploaded file could work
	// could a view create a JSON page which could also be added to the mix?
}
