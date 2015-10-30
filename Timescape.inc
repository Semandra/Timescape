<?php

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
  ";
  return $script;
}

/**
 * Creates custom styles for timeline from Module settings
 *
*/

function Timescape_CSS($cusCss = NULL) {
	$ts_categories = (variable_get('ts_categories', array()));
	
	//$bg_color_prm = variable_get('ts_timeline_event_colors');
	//$bg_color_scd = variable_get('ts_timeline_event_colors');
	//$font-size = variable_get('ts_timeline_event_colors');
	//$font = variable_get('ts_timeline_event_colors');
	$cusCss = "#Timescape .Timescape_active {
					border:" . variable_get('ts_timeline_border') . ";
					}";
	
	
	// Create styles for each of the categories
	foreach ($ts_categories as $ts_category){
		$evt_color = variable_get('ts_color_p_' . $ts_category, '');
		$evt_color_band = variable_get('ts_color_s_' . $ts_category, '');
		
		
		$cusCss .= ".timeline-small-event-tape." . $ts_category . "_event {
						background-color: ". $evt_color .";
					}";
	
		$cusCss .= ".timeline-event-tape.tapeLayer0." . $ts_category . "_event , .timeline-event-tape.tapeLayer1." . $ts_category . "_event  {
						background-color: ". $evt_color_band .";
						background-image: radial-gradient(closest-side, transparent 80%, rgba(256,256,256,1) 100%), radial-gradient(closest-side, transparent 100%, rgba(256,256,256,1) 100%);
						background-size:8px 8px;
						background-position:0 0;
						border-radius: 5px;
						border-width: 5px;
					}";
	
		$cusCss .= ".timeline-event-tape.tapeLayer1.startKnown." . $ts_category . "_event {
						border-left: solid 5px ". $evt_color .";
						border-right: none;
						border-radius: 5px;
					}";
		$cusCss .= ".timeline-event-tape.tapeLayer0.startKnown.endKnown." . $ts_category . "_event {
						border-left: solid 5px ". $evt_color .";
						border-right: solid 5px ". $evt_color .";
					}";
		$cusCss .= ".timeline-event-tape.tapeLayer1.endKnown." . $ts_category . "_event  {
						border-right: solid 5px ". $evt_color .";
						border-left: none;
					}";
	
				/*  Single Event - from a date to a date */
		$cusCss .= "	.timeline-event-tape.tapeLayer0.singleDateEvent.between." . $ts_category . "_event  {
						background-color: ". $evt_color_band .";
						background-image: radial-gradient(closest-side, transparent 80%, rgba(256,256,256,1) 100%), radial-gradient(closest-side, transparent 100%, rgba(256,256,256,1) 100%);
				}
				.timeline-event-tape.tapeLayer0.singleDateEvent.between.startKnown." . $ts_category . "_event   {
					border-left: solid 5px ". $evt_color .";
					border-right: none;
				}
				 .timeline-event-tape.tapeLayer0.singleDateEvent.between.endKnown." . $ts_category . "_event   {
					border-right: solid 5px ". $evt_color .";
					border-left: none;	
				}
				.timeline-event-tape.tapeLayer0.singleDateEvent.between.startKnown.endKnown." . $ts_category . "_event   {
					border-left: solid 5px ". $evt_color .";
					border-right: solid 5px ". $evt_color .";
				}";
				
				/*  Single Event - single date */
			$cusCss .= "	 .timeline-event-tape.tapeLayer0.singleDateEvent." . $ts_category . "_event   {
				
				}
				 .timeline-event-tape.tapeLayer0.singleDateEvent.startKnown." . $ts_category . "_event   {
					border-left: solid 4px ". $evt_color .";
					border-right: none;
				}
				 .timeline-event-tape.tapeLayer0.singleDateEvent.endKnown." . $ts_category . "_event   {
					border-right: solid 4px ". $evt_color .";
					border-left: none;	
				}
				 .timeline-event-tape.tapeLayer0.singleDateEvent.startKnown.endKnown." . $ts_category . "_event , .timeline-event-tape.tapeLayer1.startKnown.endKnown." . $ts_category . "_event  {
					border-left: solid 4px ". $evt_color .";
					border-right: solid 4px ". $evt_color .";
				}";
			};


 	 drupal_add_http_header('Content-Type', 'text/css');

  if (isset($cusCss)) {
    echo $cusCss;
  }	
	
}

/**
 * Generates XML that is used by the timeline
 *
 * Uses the php DOM functions to generate XML from databases and static
 * content. This function does not return a drupal formatted page but an
 * XML-file formatted as an attachment.
 *
*/
function Timescape_XML() {
  drupal_add_http_header('Content-Type', 'text/xml');
  //drupal_add_http_header('Content-Disposition', 'attachment; filename=Timescape.xml;');
  
  $events = _Timescape_load();
  
 // Semandra: Removed this foreach because not using Timescape_DataBridge()
	/*	foreach (Timescape_DataBridge() as $type) {
	    $events = array_merge($events, $type);
		  }*/
  
  // Create the XML
  $dom = new DOMDocument('1.0', 'UTF-8');
  $dom->formatOutput = true;
  $data = $dom->createElement('data');
  $dataNode = $dom->appendChild($data);
  
  foreach ($events as $event) {
    $information = '';
    if (array_key_exists('institutions', $event)) { $information .= '<small><em>' . str_replace('MOH', 'Min. of Health', $event['institutions']) . '</em></small><br>'; }
    if (array_key_exists('location', $event))     { $information .= '<em>' . ucwords($event['category'] . ' @ ' . $event['location']) . '</em><hr>'; }
    if ($event['comments'])                       { $information .= $event['comments'] . '<br>'; }
    if (array_key_exists('documents', $event) && $event['documents']) {
      $files = explode(',', $event['documents']);
      $information .= '<hr><strong>Attached Files</strong><br><ul>';
      foreach ($files as $file) {
        $information .= '<li><a href="' . drupal_get_path('module', 'Timescape') . '/uploads/' . $file . '">' . 
                             str_replace('_', ' ', $file) . '</a></li>';
      }
    }  
    $information .= '</ul>';
    if (user_access('edit Timescape') and array_key_exists('id', $event)) {
      $information .= '<hr> | ' . l(t('Edit'), 'timescape/edit/' . $event['id']) . ' | ' . 
                      l(t('Delete'), 'timescape/delete/' . $event['id']) . ' |';
    }
    if ((array_key_exists('created_by', $event) and array_key_exists('updated_by', $event)) and 
        ($event['created_by'] or $event['updated_by'])) {
      $information .= '<p><small><em>';
      $information .= $event['created_by'] ? 'Created by ' . $event['created_by'] . ' ' . strftime('%Y-%m-%d %H:%M', $event['created_at']) . '<br>' : '';
      $information .= $event['updated_by'] ? 'Updated by ' . $event['updated_by'] . ' ' . strftime('%Y-%m-%d %H:%M', $event['updated_at']) : '';
      $information .= '</em></small></p>';
    }
    $node = $dom->createElement('event', $information);
    $node->setAttribute('title', $event['name']);
    $node->setAttribute('start', $event['start_date']);
    if ($event['end_date']) { $node->setAttribute('end',   $event['end_date']); }
    
    $eventNode = $data->appendChild($node);
  }
  
  echo $dom->saveXML();
  // Return that we're fine
  exit(0);
}


/**
 * Formats dates for bubble output
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
	return $date->format('d/m/Y');
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
	
	//if (variable_get('ts_show_title')){
			//if 'false' add custom styles to hide div.timeline-event-bubble-title
	//}

	foreach ($events as $event) {
		//format information [text in popup bubble] using information fields
		$information = '';
		
		//if (variable_get('ts_show_image')){
			//$information .= "<img src='" variable_get('ts_image_path') . "'>" . $event['image'] . "</h1>";
		//}
		$information .= "<p class='event-category'> " . $event['category'] . " </p>";
		$information .= $event['comments'];
	
		if (variable_get('ts_show_all_dates')){
			$information .= "<div id='dateRange'>";
			$information .= "<span class='full-event-date'> " . Date_formatter($event['start_date'],$dFormat) . " </span>";
			if ($event['start_date'] != $event['end_date']) {
				$information .= " to <span class='full-event-date'> " . Date_formatter($event['end_date'],$dFormat) . " </span>";
			}
			$information .= "</div>";
		}
		if (variable_get('ts_event_date_summary')){
			$information .= "<p class='event-date-summary'> " . $event['created_by'] . " </p>";
		}
		if (variable_get('ts_event_date_summary')){
		//	$information .= "<p class='event-date-summary'> " . $event['created_by'] . " </p>";
		}
		if (variable_get('ts_event_date_summary')){
		//	$information .= "<p class='event-date-summary'> " . $event['created_by'] . " </p>";
		}
		
		//if (variable_get('ts_show_link')){
		//	$information .= "<a href='" . $event['link'] . "'></h1>";
		//}
		
//********--TODO -- Show only to those with admin privledges
			$information .= "<div id='evntEdtBtns'><span class='tinybutton'> " . l(t('Edit'), 'timescape/edit/' . $event['id']) . " </span>";
			$information .= "<span class='tinybutton'> " . l(t('Delete'), 'timescape/delete/' . $event['id']) . " </span></div>";
		
		$node['description'] =  $information;
		
		$node['start'] = $event['start_date'];
		//$node['latestStart'] = $event[' ???? '];
		//$node['earliestEnd'] = $event[' ???? '];
		$node['end'] = $event['end_date'];
		$node['title'] = $event['name'];
		//$node['durationEvent'] = $event[' ???? '];
		//$node['icon'] = $event[' ???? '];
		//$node['image'] = $event[' ???? '];
		//$node['link'] = $event[' ???? '];
		

		
		// EVENT POINT STYLING
		// depending on the category, supply the appropriate classes
		$node['classname'] = "startKnown endKnown " . $event['category'] . "_event "; //$event['name'];
		
		array_push($var['events'], $node); 
	}
	
	//-------------- load JSON file if URL provided ---------------
	if (variable_get('ts_linked_file_path')){
	//	$fileJSON = variable_get('ts_linked_file_path');
		$url = variable_get('ts_linked_file_path');
		$request = drupal_http_request($url);
		$json_response = drupal_json_decode($request->data);
		
		foreach ($json_response as $response_data) {
			
			$information = '';
			//$information .= "<h1>" . $response_data['title'] . "</h1>";
			
			if (variable_get('ts_show_all_dates')){
				$information .= "<div>";
				$information .= "<span class='full-event-date'> " . $response_data['start'] . " </span>";
				$information .= "<span class='full-event-date'> " . $response_data['end'] . " </span>";
				$information .= "</div>";
			}
			
			$response_data['description'] = $information;
			
	  		array_push($var['events'], $response_data);
		
		
			
			
		}
		
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
  $date_format = $id ? 'Y-m-d H:i:s' : 'D M d Y H:i:s \G\M\TO';
  // Return an empty event if $id == 0
  if ($id === 0) {
    return array('id'           => '',
                 'name'         => '',
                 'location'     => '',
                 'start_date'   => '',
                 'end_date'     => '',
                 'display_date' => '',
                 'category'     => '',
                 'comments'     => '',
                 'documents'    => '',
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
      if ($id and $id == $record['id']) {
        return $record;
      }
      array_push($events, $record);
    }
    return $events;
  }
  catch (Exception $e) {
    drupal_set_message($e, 'error');
    return array();
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
  $form['name'] = 
    array('#type' => 'textfield',
	  '#title' => t('Name of the timeline event (label)'),
	  '#size' => 75,
	  '#maxlength' => 255,
	  '#description' => t("Enter the name of the event you want to log"),
	  '#required' => TRUE,
	  '#default_value' => $values['name']
	  );
  $form['location'] = //THIS IS NOT A FIELD I NEED TO MAKE MANDITORY - NEED TO HAVE?
    array('#type' => 'textfield',
    '#title' => t('Location (optional)'),
    '#size' => 75,
    '#maxlength' => 255,
    '#description' => t("Location is added to the title in the popup bubble."),
    '#required' => FALSE,
	  '#default_value' => $values['location']
    );
  $form['start_date'] = 
    array('#type' => 'textfield',
    '#id' => "timescape_start_date",
    '#prefix' => "<table><tr><td>",
    '#suffix' => "</td>",
    '#title' => t('Start time'),
    '#size' => 30,
    '#maxlength' => 40,
    '#description' => t("Enter the start time of the event (YYYY-MM-DD HH:MM)."),
    '#required' => TRUE,
	  '#default_value' => $values['start_date']
    );
  $form['end_date'] = 
    array('#type' => 'textfield',
    '#id' => "timescape_end_date",
    '#prefix' => "<td>",
    '#suffix' => "</td></tr></table>",
    '#title' => t('End time'),
    '#size' => 30,
    '#maxlength' => 40,
    '#description' => t("Enter the end time of the event (YYYY-MM-DD HH:MM)."),
    '#required' => FALSE,
	  '#default_value' => $values['end_date']
    );
/*  $form['display_date'] = //Semandra - Added display date, rather than using start_date, end_date, etc.
    array('#type' => 'textfield',
    '#title' => t('Date or time description to use in the text (i.e. rather than the start date)'),
    '#size' => 75,
    '#maxlength' => 255,
    '#description' => t("Enter a human readable date description (e.g. Fall 2014, May-June 2014, etc.)."),
    '#required' => FALSE,
	  '#default_value' => $values['display_date']
    );*/
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
  $form['comments'] = 
    array('#type' => 'textarea',
    '#title' => t('Details of Event'),
    '#description' => t("Enter description of the event (appears in popup bubble). HTML formatting is okay to styles to the description or to add links."),
    '#required' => FALSE,
    '#default_value' => $values['comments'],
    );
/*  if ($values['documents']) {
    $filenames = array();
    $file_values = array();
    foreach ( explode(',', $values['documents']) as $filename ) {
      $filenames[$filename] = str_replace('_', ' ', $filename);
      array_push($file_values, $filename);
    }
    $form['documents_earlier'] = 
      array('#type' => 'checkboxes',
      '#title' => 'Previously attached files',
      '#options' => $filenames,
      '#default_value' => $file_values,
      );
  }
  $form['documents'] = 
    array('#type' => 'file',
    '#attributes' => array('class' => array('multi'),
                           'name' => 'files[]'),
    '#title' => t('Attached Files'),
    '#description' => t("Upload files that are related to the event."),
    '#required' => FALSE,
  );*/
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
  $date_regexp = '/\d{4}-\d{2}-\d{2} \d{2}:\d{2}/';  //TO-DO allow for this to be set for dates:  full, including time, to just year. (3 options)
  
  if (!preg_match($date_regexp, $form_state['values']['start_date'])) {
		form_set_error('event_start', t('You must enter a start date in the form (YYYY-MM-DD HH:MM) e.g. 2010-11-04 15:58.'));
  }
  
  if (!empty($form_state['values']['end_date']) and !preg_match($date_regexp, $form_state['values']['end_date'])) {
		form_set_error('event_end', t('You must enter an end date in the form (YYYY-MM-DD HH:MM) e.g. 2010-11-05 17:00.'));
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
  // TODO: implement proper file handling
  // Semandra - removed file handling -- not needed.
  try {
/*    foreach ($_FILES['files']['name'] as $key => $filename) {
      if (!$_FILES['files']['error'][$key]) {
        // Convert all white-space to underlines to get nicer URLs
        $filename = str_replace(' ', '_', $filename);
        $path = drupal_get_path('module', 'Timescape') . '/uploads/';
        // a VERY basic check if file exists, just adding a _ at the beginning
        // until the name is unique. TODO: better filename collision renaming.
        while (file_exists($path . $filename)) {
          $filename = '_' . $filename;
        }
        if (move_uploaded_file($_FILES['files']['tmp_name'][$key], $path . $filename)) {
          $form_state['values']['documents'] .= $filename . ',';
        }
      }
    }
    if ($form_state['values']['documents']) {
      $form_state['values']['documents'] = substr($form_state['values']['documents'], 0, -1);
    }
    if (in_array('documents_earlier', array_keys($form_state['values']))) {
      foreach ($form_state['values']['documents_earlier'] as $previous) {
        if ($previous) {
          if ($form_state['values']['documents']) {
            $form_state['values']['documents'] .= ',' . str_replace(' ', '_', $previous);
          } else {
            $form_state['values']['documents'] .= str_replace(' ', '_', $previous);
          }
        }
      }
    }*/
    $category = $form_state['values']['category'] == 'other' ? $form_state['values']['category_other'] : $form_state['values']['category'];
    $fields = array('name' => $form_state['values']['name'], 
                 'location' => $form_state['values']['location'], 
                 'start_date' => strtotime($form_state['values']['start_date']), 
                 'end_date' => strtotime($form_state['values']['end_date']) 
                               ? strtotime($form_state['values']['end_date']) 
                               : NULL, 
                 //'institutions' => str_replace(', 0', '', implode(', ', $form_state['values']['institutions'])), 
                 'category' => $category,
                 'comments' => $form_state['values']['comments'], );
                // 'documents' => $form_state['values']['documents'],);  //Semandra - took this out because don't need documents
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
  // Unless the transaction was rolled back, it gets commited here 
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
