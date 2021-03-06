<?php

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

/**
 * @file
 *   Functions and constants used by the Timescape module
*/

/** 
 * Generates javascript to initialize the timeline.
 *
 * The script does several things, first it adds the "Timescape_active" class to
 * the Timescape_timeline div in the Timescape block. This unhides the div and 
 * allows us to style it. 
 * Having this function generated from php allows us to add a properly 
 * formatted url on where to load the timeline xml.
 *
 * @return string $script
 *   A jQuery javascript that will initialize the timeline.
*/
function Timescape_jQuery() {
  $script = "
  (function ($) {

    Drupal.behaviors.Timescape = {
      attach: function(context, settings) {
        if ($('#Timescape').length) {
          $(document).ready(function() {
            	$('#Timescape_timeline').addClass('Timescape_active');
            	//Timescape_onLoad('" . url('timescape/xml') . "', 'Timescape_timeline'); //Creates an attached document generated at runtime from database table
				//Timescape_onLoad('" . url('sites/all/files/timeline_test.xml') . "', 'Timescape_timeline'); //Semandra-XML format
				//Timescape_onLoad('" . url('sites/all/files/PK-Timeline-Data-v01.json') . "', 'Timescape_timeline'); //Semandra-JSON format
				//Timescape_onLoad('" . url('sites/all/files/PK_sample_2.json') . "', 'Timescape_timeline'); //Semandra-JSON format
				Timescape_onLoad('" . url('timescape/json') . "', 'Timescape_timeline'); //JSON created from Timescape data table
				//Timescape_onLoad('" . url('sites/all/files/test-database-generated.json') . "', 'Timescape_timeline'); //tweaked JSON from database
				
				
				console.log('Im loaded');
      	  });
    	  }
        if ($('#Timescape_input').length) {
          $(document).ready(function() {
            $('#timescape_start_date').AnyTime_picker( { format: '%Y-%m-%d %H:%i' } );
            $('#timescape_end_date').AnyTime_picker(   { format: '%Y-%m-%d %H:%i' } );
            
            $('#timescape_controls').html('<a id=\"timescape_all\">Select All</a><a id=\"timescape_none\">Select None</a>');
            $('#timescape_all').bind('click', function() {
              $('.timescape_checkboxes input').each(function(){
                this.checked = true;
              });
            });
            $('#timescape_none').bind('click', function() {
              $('.timescape_checkboxes input').each(function(){
                this.checked = false;
              });
            });
            
            if ($('#timescape_category').val() != 'other') {
              $('#timescape_other').hide();
            }
            $('#timescape_category').bind('change', function() {
              if ($('#timescape_category').val() == 'other') {
                $('#timescape_other').show();
              } else {
                $('#timescape_other').hide();
              }
            });
      	  });
    	  }
      }
    };

  })(jQuery);
  
  //Used for timeline centering links - Semandra
	function centerTimeline(year) {
	  tl.getBand(0).setCenterVisibleDate(new Date(year, 0, 1));
  };
   var d = Timeline.DateTime.parseGregorianDateTime('" . variable_get('ts_center_year', '1900') . "');
   
   var tsPrmWdth = " . variable_get('ts_primary_height', '80') . "; // Height primary interval
	var tsSecWdth = " . variable_get('ts_secondary_height', '20') . "; // Height secondary interval
	var tsPrmIntvl = " . variable_get('ts_primary_interval', '7') . "; // Display primary interval 
	var tsScndIntvl = " .variable_get('ts_secondary_interval', '8') . "; // Display secondary interval
	var tsDirction = " .variable_get('ts_event_paint_direction', '1') . ";// Direction of event stacking

   var theme = Timeline.ClassicTheme.create(); // alter the defaults of the custom theme
	  theme.event.bubble.width = 450;   // modify it
	  theme.event.bubble.height = 400;
	  theme.event.track.height = 30;
	  theme.event.track.gap = 5;
	  theme.event.tape.height = " . variable_get('ts_tape_height') . ";
	  theme.event.duration.impreciseOpacity = 100;
	  theme.event.instant.impreciseOpacity = 100;  
  ";
  return $script;
}

/**
 * Creates custom styles for timeline from Module settings
 * Generates a css page which is then loaded into the header (Timescape.module line 72)
*/

function Timescape_CSS($cusCss = NULL) {
	$ts_categories = (variable_get('ts_categories', array()));
	$cusCss = "";
	$cusCss .= "#Timescape .Timescape_active {";
		$cusCss .= (variable_get('ts_tl_width')) ? "width:" . variable_get('ts_tl_width') . ";" : "";
		$cusCss .= (variable_get('ts_tl_height')) ? "height:" . variable_get('ts_tl_height') . ";" : "";
		$cusCss .= (variable_get('ts_timeline_border')) ? "border:" . variable_get('ts_timeline_border') . ";" : "";
		$cusCss .= (variable_get('ts_tape_font_family')) ? "font-family:" . variable_get('ts_tape_font_family') . ";" : "auto";
	$cusCss .= " }";
	
	$cusCss .= "#Timescape .timeline-band-0 .timeline-ether-bg {";
		$cusCss .= (variable_get('ts_tl_prm_bg_color')) ? "background-color:" . variable_get('ts_tl_prm_bg_color') . ";" : "";
	$cusCss .= " }";
	$cusCss .= "#Timescape .timeline-band-1 .timeline-ether-bg {";
		$cusCss .= (variable_get('ts_tl_sec_bg_color')) ? "background-color:" . variable_get('ts_tl_sec_bg_color') . ";" : "";
	$cusCss .= " }";
	$cusCss .= "#Timescape #timeline-band-0 .timeline-band-events{";
		$cusCss .= (variable_get('ts_tape_font_size')) ? "font-size:" . variable_get('ts_tape_font_size') . ";" : "auto";
	$cusCss .= " }";
	
	
	// Create styles for each of the categories
	foreach ($ts_categories as $ts_category){
		#lower case and spaces to underscores
		$ts_category = str_replace(' ', '_', strtolower($ts_category));
		
		$evt_color = variable_get('ts_color_p_' . $ts_category, '');
		$evt_color_band = variable_get('ts_color_s_' . $ts_category, '');
		$tape = variable_get('ts_tape_height');
		$border = $tape / 2;
		
		$cusCss .= "#Timescape .timeline-small-event-tape." . $ts_category . "_event {
						background-color: ". $evt_color .";
					}";
	
		$cusCss .= "#Timescape .timeline-event-tape.tapeLayer0." . $ts_category . "_event , #Timescape .timeline-event-tape.tapeLayer1." . $ts_category . "_event  {
						background-color: ". $evt_color_band .";
						border-radius: ". $border ."px;
						border-width: ". $border ."px;
						border-left: solid ". $border ."px ". $evt_color_band .";
						border-right: solid ". $border ."px ". $evt_color_band .";
					}";
	
		$cusCss .= "#Timescape .timeline-event-tape.tapeLayer0.startKnown." . $ts_category . "_event {
						border-left: solid ". $border ."px ". $evt_color .";
						border-right: solid ". $border ."px ". $evt_color_band .";
						border-radius: ". $border ."px;
					}";
		$cusCss .= "#Timescape .timeline-event-tape.tapeLayer0.startKnown.endKnown." . $ts_category . "_event {
						border-left: solid ". $border ."px ". $evt_color .";
						border-right: solid ". $border ."px ". $evt_color .";
					}";
		$cusCss .= "#Timescape .timeline-event-tape.tapeLayer0.endKnown." . $ts_category . "_event  {
						border-right: solid ". $border ."px ". $evt_color .";
						border-left: solid ". $border ."px ". $evt_color_band .";
					}";				
		$cusCss .= "#Timescape .timeline-event-tape.tapeLayer0.between." . $ts_category . "_event , #Timescape .timeline-event-tape.tapeLayer1.between." . $ts_category . "_event  {
					background-color: ". $evt_color_band .";
					background: radial-gradient(". $evt_color_band ." 0px, ". $evt_color_band ." 50%, rgba(0, 0, 0, 0) 70%, rgba(0, 0, 0, 0) 100%) 0px 0px;		
					background-size:". $tape ."px ". $tape ."px;
					background-position:0 0;
					border-radius: ". $border ."px;
					border-left: solid ". $border ."px ". $evt_color_band .";
					border-right: solid ". $border ."px ". $evt_color_band .";
				}
					#Timescape .timeline-event-tape.tapeLayer0.singleDateEvent.between.startKnown." . $ts_category . "_event   {
					border-left: solid ". $border ."px ". $evt_color .";
					border-right: solid ". $border ."px ". $evt_color_band .";
				}
				 #Timescape .timeline-event-tape.tapeLayer0.singleDateEvent.between.endKnown." . $ts_category . "_event   {
					border-right: solid ". $border ."px ". $evt_color .";
					border-left: solid ". $border ."px ". $evt_color_band .";
				}
				#Timescape .timeline-event-tape.tapeLayer0.singleDateEvent.between.startKnown.endKnown." . $ts_category . "_event   {
					border-left: solid ". $border ."px ". $evt_color .";
					border-right: solid ". $border ."px ". $evt_color .";
				}";
	
			};
			
			$cusCss .= (variable_get('ts_user_styles')) ? variable_get('ts_user_styles') : "";
			
	// Hide bubble title if turned off in settings
	if (!variable_get('ts_show_bubble_title')){
		$cusCss .= ".timeline-event-bubble-title { display: none;}";		
	} 
	
	// Hide Edit/Delete link if not logged-in
	if (!user_is_logged_in()){
		drupal_set_message(t("User is logged in"));
		$cusCss .= "#evntEdtBtns { display: none;}";		
	} 	
	
 	drupal_add_http_header('Content-Type', 'text/css');

  if (isset($cusCss)) {
    echo $cusCss;
  }	
}


/**
 * Formats dates for bubble output from MDY, ymd, and unix to d/m/Y
 *
*/
function Date_formatter ($dateString, $dFormat){
	$date = new DateTime($dateString);
	if ($dFormat == 'MDY') {
		return $date->format('F jS, Y');
	}
	if ($dFormat == 'ymd') {
		return $date->format('Y-m-d');
	}
	if ($dFormat == 'unix') {
		return $date("d/m/Y", $dateString);
	}
	return $date->format('d/m/Y');
}

function Date_formatter_unix ($unixTime){
	return gmdate("Y-m-d", $unixTime);
}

/**
 * Generates timeline JSON from Timescape_event table
 *
 * Uses the php DOM functions to generate JSON from databases and static
 * content. This function does not return a drupal formatted page but an
 * JSON-file formatted as an attachment.
 * 
 *
*/
function Timescape_JSON($var = NULL) {
	$events = _Timescape_load();
	//$var = $events;
	$var = array('events'=>[]);
	$dFormat = variable_get('ts_date_format');
	$srtKwn = "";
	$endKwn = "";
	$btwn = "";
	
	if (variable_get('ts_show_bubble_title')){
		$new_css = variable_get('ts_user_styles') + ".page-timescape .timeline-event-bubble-title {display: inherit;}";
		variable_set('ts_user_styles', $new_css);
	}else{
		$new_css = variable_get('ts_user_styles') + ".page-timescape .timeline-event-bubble-title {display: none;}";
		variable_set('ts_user_styles', $new_css);
		
	}
	//variable_get('ts_user_styles');

	foreach ($events as $event) {
		//format information [text in popup bubble] using information fields
		$information = '';
				
		if (variable_get('ts_show_subtitle')){
			$information .= "<p class='sub-title'> " . $event['sub_title'] . " </p>";
		}	
		if (variable_get('ts_show_category')){
			$information .= "<p class='event-category'> " . $event['category'] . " </p>";
		}
		if (variable_get('ts_show_location')){
			$information .= "<p class='sub-title location'> " . $event['location'] . " </p>";
		}
		if (variable_get('ts_show_body_text')){
			$information .= "<p class='description'> " . $event['description'] . " </p>";
		}
	
		if (variable_get('ts_show_all_dates')){
			$information .= "<div id='dateRange'>";
			$information .= "<span class='full-event-date'> " . Date_formatter($event['start_date'],$dFormat) . " </span>";
			if ($event['end_date']) {
				$information .= " to <span class='full-event-date'> " . Date_formatter($event['end_date'],$dFormat) . " </span>";
			}
			$information .= "</div>";
		}
		
		if (variable_get('ts_show_sub_text')){
			$information .= "<p class='event-sub-text'> " . $event['sub_text'] . " </p>";
		}
		
		

		//===========================================================================
		
		// Explicit display of all timeline start and end dates
		if (variable_get('ts_event_timeline_dates')){
			$information .= "<p>Start: " . $event['start_date'];
			if ($event['late_start']){
				$information .= " - Latest start: " . $event['late_start'];
			}
			if ($event['early_end']){
				$information .= " - Earliest end: "  . $event['early_end'];
			}
			if ($event['end_date']){
				$information .= " - End: " . $event['end_date'];
			}
			$information .= "</p>";
		}
		
		
		if (variable_get('ts_event_date_summary')){
			$information .= "<span class='event-date-summary'> Created: " . $event['created_by'] . " </span >";
		}
		if (variable_get('ts_event_date_summary')){
			if ($event['created_at']) {
				$information .= "<span  class='event-date-summary'> " . Date_formatter_unix($event['created_at']) . " </span >";
			}else{
				$information .= "<span  class='event-date-summary'> unknown </span >";
			}
		}
		if (variable_get('ts_event_date_summary') && $event['updated_at'] != 0){
			$information .= "<span  class='event-date-summary'> - Last updated: " . $event['updated_by'] . " </span >";
		}
		if (variable_get('ts_event_date_summary') && $event['updated_at'] != 0){
			$information .= "<span  class='event-date-summary'> " . Date_formatter_unix($event['updated_at']) . " </span >";
		}
		
		//if (variable_get('ts_show_link')){
		//	$information .= "<a href='" . $event['link'] . "'></h1>";
		//}
		
		if ($event['id']){
			$information .= "<div id='evntEdtBtns'><span class='tinybutton'> " . l(t('Edit'), 'timescape/edit/' . $event['id']) . " </span>";
			$information .= "<span class='tinybutton'> " . l(t('Delete'), 'timescape/delete/' . $event['id']) . " </span></div>";
		}
		$node['title'] = $event['title'];
		$node['start'] = $event['start_date'];
		$node['end'] = $event['end_date'];
		//$node['latestStart'] = $event['late_start'];
		//$node['earliestEnd'] = $event['early_end'];	
		//$node['latestStart'] = ($event['late_start'] == NULL) ? false : $event['late_start'];
		//$node['earliestEnd'] = ($event['early_end'] == NULL) ? false : $event['early_end'];
		
		$node['durationEvent'] = ($event['duration_event'] == 0) ? false : true;
		
		//$node['durationEvent'] = $event['duration_event'];
		
		if (variable_get('ts_show_image')){
			$node['image'] = $event['image_URL'];
		}
		
		
		$node['caption'] = $event['caption'];
		$node['link'] = $event['link_URL'];
		$node['description'] =  $information;

		
		// EVENT POINT STYLING
		// depending on the category, supply the appropriate classes
		$btwn = ($event['duration_event'] == 1) ? "" : "between ";
		//$srtKwn = ($event['duration_event'] == 0) ? "" : "startKnown ";
		//$endKwn = ($event['duration_event'] == 0) ? "" : "endKnown ";
		
		// If end date is blank then fill it in and make startKnown and endKnown
		if ($event['end_date'] == NULL){
			$node['end'] = $event['start_date'];
			$srtKwn = "startKnown ";
			$endKwn = "endKnown ";
		}
		// If precise_start is true then add startKnown
		if ($event['late_start'] == NULL){
			$srtKwn = "startKnown ";
		}
		// If precise_end is true then add endKnown
		if ($event['early_end'] == NULL){
			$endKwn = "endKnown ";
		}
		
		if ($event['early_end'] != NULL && $event['early_end'] != $event['end_date']){
			$endKwn = " ";
		}
		if ($event['late_start'] != NULL && $event['late_start'] != $event['start_date']){
			$srtKwn = " ";
		}
		
		//$srtKwn = " ";
		//$endKwn = " ";
		//$btwn = "between ";
		
		$event_category = str_replace(' ', '_', strtolower($event['category']));
		
		$node['classname'] = $srtKwn . $endKwn . $btwn . $event_category . "_event "; //$event['name'];
	
		
		array_push($var['events'], $node); 
	}
	
	// We are returning JSON, so tell the browser.
 	 drupal_add_http_header('Content-Type', 'application/json');

  if (isset($var)) {
    echo drupal_json_encode($var);
  }
 
}


/**
 * Loads event information from the database
 *
 * This function uses drupal's built in database handlers to return a formatted
 * array of records that can later be converted to JSON (or XML) for the timeline [function Timescape_XML()].
 *
 * @param int $id
 *   Loads only the given $id
 *
 * @return array(array) $events
 *   An associative array of arrays describing the database table.
*/
function _Timescape_load($id = NULL) {
  //$date_format = $id ? 'Y-m-d H:i:s' : 'D M d Y H:i:s \G\M\TO';
  $date_format = $id ? 'Y-m-d' : 'M d Y';
  
  // Return an empty event if $id == 0
  if ($id === 0) {
    return array('id'           => '',
                 'title'        => '',  
                 'start_date'   => '',
                 'end_date'     => '',
				 'late_start'     => '',
				 'early_end'     => '',
				 'duration_event'     => '',
				 'category'     => '',
				 'location'     => '',
				 'sub_title'     => '',
                 'description' => '',
                 'sub_text'     => '',
                 'caption'     => '',
                 'image_URL'    => '',
				 'link_URL'    => '', 
                 'created_by'   => '',
                 'created_at'   => '',
                 'updated_by'   => '',
                 'updated_at'   => '',);
  }
  try {
    $events = array();
    $records = db_select('timescape_event', 't')
                        ->fields('t') // Equivalent of "SELECT * FROM"
                        ->execute();
    while ($record = $records->fetchAssoc()) {
      $record['start_date'] = date($date_format, $record['start_date']);
      $record['end_date'] = $record['end_date'] ? date($date_format, $record['end_date']) : '';
	  $record['late_start'] = $record['late_start'] ? date($date_format, $record['late_start']) : '';
	  $record['early_end'] = $record['early_end'] ? date($date_format, $record['early_end']) : '';
      if ($id and $id == $record['id']) {
        return $record;
      }
      array_push($events, $record);
    }
    //return $events;
  }
  catch (Exception $e) {
    drupal_set_message($e, 'error');
    return array();
  }
  if (variable_get('ts_json_file_path')){
	//	$fileJSON = variable_get('ts_linked_file_path');
		$url = variable_get('ts_json_file_path');
		$request = drupal_http_request($url);
		$json_response = drupal_json_decode($request->data);
		
		foreach ($json_response as $response_entry) {
			//drupal_set_message('<pre>'. print_r($response_entry, true) .'</pre>');
			array_push($events, $response_entry);
		}
		
		return $events;
	}else{
		return $events;
	}
}


/**
 * A form to input new events to the timeline.
 *
 * This function uses JQuery UI functions to make input neater. If you wish to
 * avoid depending on the JQuery UI module modify this function. Nothing else
 * uses jQuery UI.
 *
 * @param array $form
 *   The form that is to be generated, supplied by drupal
 * @param array &$form_state
 *   The current state of the form, supplied by drupal
 *
 * @return array $form
 *   A form to input new events.
*/
function _Timescape_Input($form, &$form_state, $values) {
	$categories = array();
	$results = db_select('timescape_event','t')
											 ->distinct()
                       ->fields('t', array('category'))
                       ->execute();
	while ($result = $results->fetchAssoc()) {
		$categories[$result['category']] = $result['category'];
	}
	$categories['other'] = 'Other';
  $form['id'] =
    array('#type' => 'hidden',
    '#value' => $values['id'],
    );
  $form['title'] = 
    array('#type' => 'textfield',
	  '#title' => t('Name of the timeline event (label)'),
	  '#size' => 75,
	  '#maxlength' => 255,
	  '#description' => t("Enter the name of the event you want to chart. [Note: HTML is okay. e.g. <i>Title</i>]"),
	  '#required' => TRUE,
	  '#default_value' => $values['title'],
	  );
  $form['start_date'] = 
    array('#type' => 'textfield',
		'#id' => "timescape_start_date",
		//'#prefix' => "<table><tr><td>",
		//'#suffix' => "</td>",
		'#title' => t('Start time'),
		'#size' => 30,
		'#maxlength' => 40,
		'#description' => t("Enter the start time of the event (YYYY-MM-DD HH:MM). [Note: HH:MM is optional]"),
		'#required' => TRUE,
	  '#default_value' => $values['start_date']
    );
//	$form['start_precise'] = 
//    array('#type' => 'checkbox',
//	  '#title' => t('Precise Date'),
//	  //'#description' => t("Known or estimated"),
//	  '#required' => TRUE,
//	  '#default_value' => 1,
//	  );
	$form['late_start'] = 
    array('#type' => 'textfield',
		'#id' => "timescape_start_date",
		//'#prefix' => "<table><tr><td>",
		//'#suffix' => "</td>",
		'#title' => t('Latest start time'),
		'#size' => 30,
		'#maxlength' => 40,
		'#description' => t("If an estimate enter the latest start time of the event (YYYY-MM-DD HH:MM)."),
		'#required' => FALSE,
	  '#default_value' => $values['late_start']
    );
  $form['end_date'] = 
    array('#type' => 'textfield',
    '#id' => "timescape_end_date",
  //  '#prefix' => "<td>",
  //  '#suffix' => "</td></tr></table>",
    '#title' => t('End time'),
    '#size' => 30,
    '#maxlength' => 40,
    '#description' => t("Enter the end time of the event (YYYY-MM-DD HH:MM)."),
    '#required' => FALSE,
	  '#default_value' => $values['end_date']
    );
	$form['early_end'] = 
    array('#type' => 'textfield',
		'#id' => "timescape_end_date",
		//'#prefix' => "<td>",
//		'#suffix' => "</td></tr></table>",
		'#title' => t('Earliest End time'),
		'#size' => 30,
		'#maxlength' => 40,
		'#description' => t("Enter the Earliest End time of the event (YYYY-MM-DD HH:MM)."),
		'#required' => FALSE,
		  '#default_value' => $values['early_end']
    );
	$active = array(0 => t('No'), 1 => t('Yes'));
	$form['duration_event'] = 
		array('#type' => 'radios',
		'#title' => t('Duration Event'),
		'#options' => $active,
		'#maxlength' => 255,
		'#description' => t("Event happend continuously between two dates"),
		'#required' => FALSE,
		'#default_value' => isset($values['duration_event']) ? $values['duration_event'] : 0,
    );
  $form['category'] = 
    array('#type' => 'select',
    '#id' => 'timescape_category',
    '#title' => t('Category'),
    '#options' => $categories,
    '#description' => t("Select the category that this event falls in."),
    '#required' => FALSE,
    '#default_value' => $values['category'],
    );
  $form['category_other'] = 
    array('#type' => 'textfield',
    '#prefix' => '<div id="timescape_other">',
    '#suffix' => '</div>',
    '#size' => 30,
    '#maxlength' => 50,
	'#required' => FALSE,
    '#description' => t("Create new category (required for first event). Select 'other' from category to create a new category name."),
    '#default_value' => $values['category']
    );
  $form['location'] = 
	  array('#type' => 'textfield',
	  '#title' => t('Location (optional)'),
	  '#size' => 75,
	  '#maxlength' => 255,
	  '#description' => t("Location is added to the title in the popup bubble."),
	  '#required' => FALSE,
		'#default_value' => $values['location']
  );
  $form['sub_title'] = 
    array('#type' => 'textfield',
    '#title' => t('Subtitle'),
    '#size' => 75,
    '#maxlength' => 255,
    '#description' => t("Can be styled as subtitle or as a replacement title."),
    '#required' => FALSE,
	  '#default_value' => $values['sub_title']
    );
  $form['description'] = 
    array('#type' => 'textarea',
    '#title' => t('Details of Event'),
    '#description' => t("Enter description of the event (appears in popup bubble). HTML formatting is okay to styles to the description or to add links."),
    '#required' => FALSE,
    '#default_value' => $values['description'],
    );
	
	$form['sub_text'] = 
    array('#type' => 'textfield',
    '#title' => t('Sub-text'),
    '#description' => t("Optional text area. (i.e. Used as a human friendly date replacement -- e.g.'Fall 2015')"),
    '#required' => FALSE,
    '#default_value' => $values['sub_text'],
    );
	$form['caption'] = 
    array('#type' => 'textfield',
    '#title' => t('Caption'),
    '#size' => 75,
    '#maxlength' => 255,
    '#description' => t("Mouseover tool-tip showing in timeline view."),
    '#required' => FALSE,
	  '#default_value' => $values['caption']
    );
	$form['image_URL'] = 
    array('#type' => 'textfield',
    '#title' => t('Image'),
    '#size' => 75,
    '#maxlength' => 255,
    '#description' => t("Full image URL (shows in popup bubble)."),
    '#required' => FALSE,
	  '#default_value' => $values['image_URL']
    );
	
	// URL link field -- becomes link for title in bubble popup
	if (variable_get('ts_show_url_in_title')){
		$form['link_URL'] = 
		array('#type' => 'textfield',
		'#title' => t('Link URL'),
		'#size' => 75,
		'#maxlength' => 255,
		'#description' => t("Link URL (Title becomes link in popup bubble - use full URL, e.g. http://example.com, for external links)."),
		'#required' => FALSE,
		  '#default_value' => $values['link_URL']
		);
	}
	
  $form['event_submit'] = 
    array('#type' => 'submit',
    '#value' => "Submit Form",
    '#title' => t('Submit.'),
    );
  return $form;
}

/**
 * Validates the input from _Timescape_Input before it is saved to the database.
 * 
 * This function makes sure that all dates are in the expected format, that all 
 * required fields are supplied and so on.
 *
 * @param array $form
 *   The form that is to be generated, supplied by drupal
 * @param array &$form_state
 *   The current state of the form, supplied by drupal
*/
function _Timescape_Input_validate(&$form, &$form_state) {
  //$date_regexp = '/\d{4}-\d{2}-\d{2} \d{2}:\d{2}/';  //TO-DO allow for this to be set for dates:  full, including time, to just year. (2 options)
  $date_regexp = '/\d{4}-\d{2}-\d{2}/';
  
  if (!preg_match($date_regexp, $form_state['values']['start_date'])) {
		form_set_error('event_start', t('You must enter a start date in the form (YYYY-MM-DD) e.g. 2010-11-04'));
  }
  
  if (!empty($form_state['values']['end_date']) and !preg_match($date_regexp, $form_state['values']['end_date'])) {
		form_set_error('event_end', t('You must enter an end date in the form (YYYY-MM-DD) e.g. 2010-11-05'));
  }
  
  if (!empty($form_state['values']['end_date']) and (strtotime($form_state['values']['start_date']) > strtotime($form_state['values']['end_date']))) {
		form_set_error('event_end', t('The end date of the event cannot be before the start date.'));
  }
  
  if ($form_state['values']['category'] == 'other' and empty($form_state['values']['category_other'])) {
		form_set_error('category', t('You need to define a category for your event.'));
  }
}

/**
 * Saves information from the input form to the database
 *
 * This is mainly a wrapper function around drupal_write_record, that formats
 * the output variables and converts timestamps to epoch time.
 *
 * @param array $form
 *   The form that is to be generated, supplied by drupal
 * @param array &$form_state
 *   The current state of the form, supplied by drupal
*/
function _Timescape_Input_submit($form_id, &$form_state) {
  $trn = db_transaction();
  global $user;
  try {

    $category = $form_state['values']['category'] == 'other' ? $form_state['values']['category_other'] : $form_state['values']['category'];
    $fields = array('title' => $form_state['values']['title'],  
                 'start_date' => strtotime($form_state['values']['start_date']), 
                 'end_date' => strtotime($form_state['values']['end_date']) 
                               ? strtotime($form_state['values']['end_date']) 
                               : NULL, 
				'late_start' => strtotime($form_state['values']['late_start']) 
                               ? strtotime($form_state['values']['late_start']) 
                              : NULL, 
				'early_end' => strtotime($form_state['values']['early_end']) 
                               ? strtotime($form_state['values']['early_end']) 
                               : NULL,
                 'duration_event' => $form_state['values']['duration_event'],
				 'category' => $category,
				 'location' => $form_state['values']['location'],
				 'sub_title' => $form_state['values']['sub_title'],
				 'description' => $form_state['values']['description'], 
				 'sub_text' => $form_state['values']['sub_text'],
				 'caption' => $form_state['values']['caption'],
				 'image_URL' => $form_state['values']['image_URL'],
                 );
	if (variable_get('ts_show_url_in_title')){
		$fields['link_URL'] = $form_state['values']['link_URL'];
	}
               
    if (!$form_state['values']['id']) {
      $fields['created_by'] = $user->name;
      $fields['created_at'] = time();
      $id = db_insert('timescape_event')
                      ->fields($fields)
                      ->execute();
    } else {
      $fields['updated_by'] = $user->name;
      $fields['updated_at'] = time();
      $id = db_update('timescape_event')
                      ->fields($fields)
                      ->condition('id', $form_state['values']['id'], '=')
                      ->execute();
    }
  }
  catch (Exception $e) {
    $trn->rollback();
    watchdog_exception('type', $e);
  }
  
	$form_state['redirect'] = 'timescape';
  	//Unless the transaction was rolled back, it gets commited here 
}

/**
 * Creates a small form to confirm event deletion.
 *
 * @param array $form
 *   The form that is to be generated, supplied by drupal
 * @param array &$form_state
 *   The current state of the form, supplied by drupal
 *
 * @return array $form
 *   The confirm deletion form.
*/
function Timescape_delete($form, &$form_state, $id) {
	$form = array();
  $form['id'] =
    array('#type' => 'hidden',
    '#value' => $id,
    );
	$form['submit'] = 
	  array('#type' => 'submit',
		'#prefix' => 'Are you sure you want to delete event ' . $id . '?',
	  '#value' => "Delete",
	  );
	return $form;
}

/**
 * Deletes an event from the database
 *
 * This function uses drupals built in database handlers and return a status
 * message once the function has run.
 *
 * @param int $id
 *   The $id to be deleted
 *
 * @return string $status
 *   Prints a status string to the screen
*/
function Timescape_delete_submit($form, &$form_state) {
  if ($form_state['values']['id']) {
    try {
      $trn = db_transaction();
      db_delete('timescape_event')
               ->condition('id', $form_state['values']['id'])
               ->execute();
    } catch (Exception $e) {
      $trn->rollback();
      watchdog_exception('type', $e);
    }
  }
	$form_state['redirect'] = 'timescape';
}
