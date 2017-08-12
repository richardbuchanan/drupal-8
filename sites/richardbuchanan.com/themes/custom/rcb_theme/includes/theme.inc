<?php

/**
 * @file
 * rcb_theme theme system, which controls the output of rcb_theme.
 *
 * The theme system allows for nearly all output of the Drupal system to be
 * customized by UIkit themes.
 */

use Drupal\Core\Link;
use Drupal\Core\Url;

/**
 * Implements hook_theme().
 */
/* -- Delete this line if you want to use this function
function rcb_theme_theme($existing, $type, $theme, $path) {
}
// */

/**
 * Implements theme_footnote_link().
 */
function rcb_theme_footnote_link($variables) {
  $fn = $variables['fn']['fn'];
  $ref_id = $fn['ref_id'];
  $text_clean = html_entity_decode($fn['text_clean']);
  $fn_id = $fn['fn_id'];
  $value = '[' . $fn['value'] . ']';

  $url = Url::fromUri('internal:');
  $link_options = [
    'attributes' => [
      'id' => $ref_id,
      'class' => [
        'see-footnote',
      ],
      'title' => $text_clean,
      'uk-tooltip' => '',
    ],
    'fragment' => $fn_id,
  ];

  $url->setOptions($link_options);
  $link = Link::fromTextAndUrl($value, $url);

  return '<sup>' . $link->toString() . '</sup>';
}

/**
 * Implements theme_footnote_list().
 */
function rcb_theme_footnote_list($variables) {
  $footnotes = $variables['footnotes']['#footnotes'];
  $output = '<h3 class="uk-margin-small-bottom">References</h3>';
  $output .= '<hr class="uk-margin-small-top uk-margin-small-bottom">';
  $output .= '<ul class="footnotes uk-margin-small-top">';

  foreach ($footnotes as $fn) {
    $ref_id = $fn['ref_id'];
    $fn_id = $fn['fn_id'];
    $value = $fn['value'];
    $text = html_entity_decode($fn['text']);

    if (!is_array($ref_id)) {
      $output .= '<li class="footnote uk-margin-medium-left" id="' . $fn_id . '">';
      $output .= '<a class="footnote-label" href="#' . $ref_id . '">' . $value . '</a> ';
      $output .= $text . '</li>';
    }
    else {
      $abc = str_split("abcdefghijklmnopqrstuvwxyz"); $i = 0;
      $output .= '<li class="footnote uk-margin-medium-left" id="' . $fn_id . '">';
      $output .= '<a href="#' . $ref_id[0] . '" class="footnote-label">' . $value . '</a> ';

      foreach ($ref_id as $ref) {
        $output .= '<a class="footnote-multi" href="#' . $ref . '">' . $abc[$i] . '</a> ';
        $i++;
      }

      $output .= $text . '</li>';
    }
  }

  $output .= '</ul>';

  return $output;
}
