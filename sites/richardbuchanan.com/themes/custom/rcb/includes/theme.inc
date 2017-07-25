<?php

/**
 * @file
 * rcb theme system, which controls the output of rcb.
 *
 * The theme system allows for nearly all output of the Drupal system to be
 * customized by UIkit themes.
 */

use Drupal\Core\Link;
use Drupal\Core\Url;

/**
 * Implements theme_footnote_link().
 */
function rcb_footnote_link($variables) {
  $fn = $variables['fn']['fn'];
  $fn_id = $fn['ref_id'];
  $fn_value = $fn['value'];
  $fn_url_options = ['attributes' => ['id' => $fn_id]];
  $fn_url = Url::fromUserInput("#$fn_id", $fn_url_options);
  $fn_text = t('@text', ['@text' => $fn_value]);
  $fn_link = Link::fromTextAndUrl($fn_text, $fn_url)->toString();

  $output = '<sup class="rcb-footnote" rcb-footnote-id="' . $fn_id . '">';
  $output .= $fn_link;
  $output .= '</sup>';
  $output .= '<div rcb-footnote-popup="' . $fn_id . '" uk-dropdown="pos: top-justify">';
  $output .= html_entity_decode($variables['fn']['fn']['text_clean']);
  $output .= '</div>';

  return $output;
}

/**
 * Implements theme_footnote_list().
 */
function rcb_footnote_list($footnotes) {
  $footnotes = $footnotes['footnotes']['#footnotes'];
  $str = '<ul class="footnotes">';
  foreach ($footnotes as $fn) {
    if (!is_array($fn['ref_id'])) {
      $str .= '<li class="footnote" id="' . $fn['fn_id'] . '"><a class="footnote-label" href="#' . $fn['ref_id'] . '">' . $fn['value'] . '.</a> ';
      $str .= html_entity_decode($fn['text']) . '</li>';
    }
    else {
      $abc = str_split("abcdefghijklmnopqrstuvwxyz"); $i = 0;

      $str .= '<li class="footnote" id="' . $fn['fn_id'] . '"><a href="#' . $fn['ref_id'][0] . '" class="footnote-label">' . $fn['value'] . '.</a> ';

      foreach ($fn['ref_id'] as $ref) {
        $str .= '<a class="footnote-multi" href="#' . $ref . '">' . $abc[$i] . '.</a> ';
        $i++;
      }
      $str .= html_entity_decode($fn['text']) . '</li>';
    }
  }

  $str .= '</ul>';

  return $str;
}
