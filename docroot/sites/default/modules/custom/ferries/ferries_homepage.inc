<?php
/**
* Builds simple form for 'Find your sailing schedule by route' tile
*/
function select_route_form($form, &$form_state) {
    $form['#prefix'] = '<div class="action-box-shadow">';
    $form['#suffix'] = '</div>';
    $form['header'] = array(
        '#title' => t('Find your sailing schedule by route'),
        '#markup' => '<h2>Find your sailing schedule by route</h2>'
    );
    $form['#method'] = 'get';
    $form['#attributes']['name'] = 'schedule-by-route-form';
    $form['#attributes']['class'] = 'schedule-by-route';
    $form['#id'] = 'schedule-by-route';
    $form['#action'] = 'https://www.wsdot.com/ferries/schedule/';
    $form['submit_button'] = array(
        '#type' => 'submit',
        '#value' => t('Select route'),
    );
    
    return $form;
}

/**
* Builds simple form for 'Make reservations' tile
*/
function make_reservations_form($form, &$form_state) {
    $form['#prefix'] = '<div class="action-box-shadow">';
    $form['#suffix'] = '</div>';
    $form['header'] = array(
        '#title' => t('Save a spot for your vehicle on some routes'),
        '#markup' => '<h2>Save a spot for your vehicle on some routes</h2>'
    );
    $form['#method'] = 'get';
    $form['#attributes']['name'] = 'make-reservations-form';
    $form['#attributes']['class'] = 'make-reservations';
    $form['#id'] = 'make-reservations';
    $form['#action'] = 'https://secureapps.wsdot.wa.gov/ferries/reservations/vehicle/default.aspx';
    $form['submit_button'] = array(
        '#type' => 'submit',
        '#value' => t('Make reservations'),
    );

    return $form;
}

/**
* Builds simple form for 'Buy tickets' tile
*/
function buy_tickets_form($form, &$form_state) {
    $form['#prefix'] = '<div class="action-box-shadow">';
    $form['#suffix'] = '</div>';
    $form['header'] = array(
        '#title' => t('Buy your tickets or passes online'),
        '#markup' => '<h2>Buy your tickets or passes online</h2>'
    );
    $form['#method'] = 'post';
    $form['#attributes']['name'] = 'buy-tickets-form';
    $form['#attributes']['class'] = 'buy-tickets';
    $form['#id'] = 'buy-tickets';
    $form['#action'] = 'https://wave2go.wsdot.com/webstore/landingPage?cg=21&c=76';
    $form['submit_button'] = array(
        '#type' => 'submit',
        '#value' => t('Buy tickets'),
    );

    return $form;
}

/**
* Builds HTML for 'Ferry alerts' tile
*/
function build_ferry_alerts() {
    $json = file_get_contents("https://data.wsdot.wa.gov/ferries/WSFRouteAlert.js");
    $alert = json_decode($json, true);
    $publishDate = $alert[0]["PublishDate"];
    $alertFullTitle = $alert[0]['AlertFullTitle'];

    $output = "<div style='position: relative; box-sizing: border-box; min-height: 12.5rem; padding: 8px 13px 8px 13px; background-color: rgba(255,106,19,0.05);'>";
    $output .= "  <h2 class='pane-title'>Ferry alerts</h2>";
    $output .= "  <div style='font-size: 0.875rem;'>" . $publishDate . "</div>";
    $output .= "  <div style='font-size: 1.125rem; font-weight: bold; padding: .75rem 0 1.5rem 0;'>" . $alertFullTitle . "</div>";
    $output .= "  <ul class='info-box' style='position: absolute; bottom: 0; left: 13px;'>";
    $output .= "    <li><a href='https://www.wsdot.wa.gov/ferries/schedule/bulletin.aspx'>All alerts</a></li>";
    $output .= "  </ul>";
    $output .= "</div>";

    return $output;
}

/**
* Builds HTML for 'Social media icons' block
*/
function build_social_media_icons() {
    $output = "<div id='social-media-container'>";
    $output .= "  <a href='https://www.flickr.com/photos/wsdot/collections/72157604556431407/'>";
	$output .= "    <img src='/sites/default/themes/custom/ferries/images/flickr-icon.png' alt='Flickr icon'>";
	$output .= "  </a>";
    $output .= "  <a href='https://twitter.com/wsferries/'>";
	$output .= "    <img src='/sites/default/themes/custom/ferries/images/twitter-icon.png' alt='Twitter icon'>";
	$output .= "  </a>";
    $output .= "  <a href='https://www.facebook.com/wsferries/'>";
	$output .= "    <img src='/sites/default/themes/custom/ferries/images/facebook-icon.png' alt='Facebook icon'>";
	$output .= "  </a>";
    $output .= "</div>";

    return $output;
}

/**
* Builds HTML for 'Live ferry status' tile
*/
function build_live_ferry_status() {
    $output = "<div style='position: relative; box-sizing: border-box; min-height: 12.5rem; padding: 8px 13px 8px 13px; background-color: rgba(151,215,0,0.05);'>";
    $output .= "  <h2 class='pane-title'>Live ferry status</h2>";
    $output .= "  <ul class='info-box'>";
    $output .= "    <li><a href='https://www.wsdot.com/ferries/vesselwatch/'>Real-time map</a></li>";
    $output .= "    <li><a href='https://www.wsdot.wa.gov/ferries/vesselwatch/terminals.aspx'>Boarding status by terminal</a></li>";
    $output .= "  </ul>";
    $output .="</div>";

    return $output;
}

/**
* Builds HTML for 'Get to know your ferries' tile
*/
function build_get_to_know_your_ferries() {
    $output = "<div style='padding: 0 13px 8px 13px;'>";
    $output .= "  <h2 class='pane-title'>Get to know your ferries</h2>";
    $output .= "  <div style='font-size: 1.25rem; font-weight: bold;'>All are welcome on Washington State Ferries</div>";
    $output .= "  <p style='margin: 8px 0 24px 0;'>Here are some helpful tips on how to navigate the ferries.</p>";
    $output .= "  <ul class='info-box'>";
    $output .= "    <li><a href='/ferries/rider-information/first-time'>First-time rider's guide</a></li>";
    $output .= "    <li><a href='/ferries/rider-information/ada'>Riders with disabilities</a></li>";
    $output .= "    <li><a href='https://wsdot.wa.gov/ferries/pdf/WashingtonStateFerries-RouteMap.pdf'>Route map (pdf 501 kb)</a></li>";
    $output .= "    <li><a href='/ferries/rider-information/canada'>Travel to Canada</a></li>";
    $output .= "    <li><a href='https://wsdot.wa.gov/ferries/infodesk/customerfeedback'>Contact Ferries</a></li>";
    $output .= "  </ul>";
    $output .= "</div>";

    return $output;
}
