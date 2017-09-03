<?php

/**
 * @file
 * Set up variables to be placed within the template (.html.twig) files.
 *
 * The variables set up here apply to both templates (.html.twig) files and
 * functions (theme_HOOK). These are also used for providing
 * @link https://www.drupal.org/node/2354645 Twig Template naming conventions @endlink.
 *
 * @see process.inc
 */

use Drupal\Component\Utility\Html;
use Drupal\Core\Template\Attribute;
use Drupal\Core\Datetime\DateFormatter;
use Drupal\rcb\RCB;

/**
 * Implements template_preprocess_region().
 */
function rcb_preprocess_region(&$variables) {
  $region = $variables['region'];

  $attributes = new Attribute;
  $get_class = Html::getClass($region);
  $get_id = Html::getId($region);
  $region_class = "region--$get_class";
  $region_id = "region--$get_id";

  $attributes->setAttribute('id', $region_id);
  $attributes->addClass('region');
  $attributes->addClass($region_class);

  switch ($region) {
    case 'content':
      $attributes->addClass('uk-width-expand');
      break;

    case 'footer':
      $attributes->setAttribute('uk-grid', '');
      break;

    case 'sidebar_first':
    case 'sidebar_second':
      $attributes->addClass('uk-width-1-1');
      $attributes->addClass('uk-width-1-4@l');
      break;
  }

  if ($region == 'sidebar_first') {
    $attributes->addClass('uk-hidden@m');
  }

  $variables['attributes'] = $attributes;
}

/**
 * Implements template_preprocess_block().
 */
function rcb_preprocess_block(&$variables) {
  $plugin_id = $variables['plugin_id'];

  switch ($plugin_id) {
    case 'system_powered_by_block':
      $content = RCB::systemPoweredByContent();
      $variables['content'] = $content;
      break;
  }
}

/**
 * Implements template_preprocess_breadcrumb().
 */
function rcb_preprocess_breadcrumb(&$variables) {
  $count = count($variables['breadcrumb']);
  $attributes = new Attribute;
  $attributes->setAttribute('id', 'system-breadcrumbs');
  $attributes->setAttribute('role', 'navigation');
  $attributes->setAttribute('aria-labelledby', 'system-breadcrumb');

  if ($count <= 1) {
    $attributes->addClass('uk-hidden');
  }

  $variables['attributes'] = $attributes;
}

/**
 * Implements template_preprocess_comment().
 */
function rcb_preprocess_comment(&$variables) {
  $comment = $variables['elements']['#comment'];
  $timestamp = $comment->getCreatedTime();
  $variables['published'] = \Drupal::service('date.formatter')->format($timestamp, 'custom', 'F j, Y');
}

/**
 * Implements template_preprocess_details().
 */
function rcb_preprocess_details(&$variables) {
  $variables['attributes']['uk-accordion'] = '';
  $variables['summary_attributes']->addClass('uk-accordion-title');
}

/**
 * Implements template_preprocess_form().
 */
function rcb_preprocess_form(&$variables) {
  $form_id = $variables['element']['#form_id'];
  $get_id = Html::getId($form_id);
  $attributes = new Attribute;
  $attributes->setAttribute('id', $get_id);
  $orientation = FALSE;

  switch ($form_id) {
    case 'contact_message_feedback_form':
      $orientation = 'horizontal';
      break;

    case 'search_block_form':
      $attributes->addClass('uk-position-relative');
      break;

    default:
      $orientation = 'stacked';
  }

  switch ($orientation) {
    case 'horizontal':
      $attributes->addClass('uk-form-horizontal');
      break;

    case 'stacked':
      $attributes->addClass('uk-form-stacked');
      break;
  }

  foreach ($variables['attributes'] as $attribute => $value) {
    if ($attribute != 'class') {
      if (is_array($value)) {
        foreach ($value as $item) {
          $attributes->setAttribute($attribute, $item);
        }
      }
      else {
        $attributes->setAttribute($attribute, $value);
      }
    }
    else {
      foreach ($value as $class) {
        $attributes->addClass($class);
      }
    }
  }

  $variables['attributes'] = $attributes;
}

/**
 * Implements template_preprocess_input().
 */
function rcb_preprocess_input(&$variables) {
  $type = $variables['element']['#type'];

  if ($type == 'submit') {
    $variables['attributes']['class'][] = 'uk-button';
    $value = $variables['element']['#value']->getUntranslatedString();

    if ($variables['attributes']['id'] != 'edit-submit--search-block-form') {
      switch ($value) {
        case 'Advanced search':
        case 'Preview':
        case 'Search':
        case 'Send message':
          $variables['attributes']['class'][] = 'uk-button-primary';
          break;

        default:
          $variables['attributes']['class'][] = 'uk-button-default';
      }
    }
    else {
      $variables['attributes']['class'][] = 'uk-button-link';
    }
  }
}

/**
 * Implements template_preprocess_node().
 */
function rcb_preprocess_node(&$variables) {
  $node = $variables['node'];

  $timestamp = $node->getCreatedTime();
  $variables['date'] = \Drupal::service('date.formatter')->format($timestamp, 'custom', 'F j, Y');
  $variables['created'] = \Drupal::service('date.formatter')->format($timestamp, 'html_datetime');
  $variables['modified'] = \Drupal::service('date.formatter')->format($timestamp, 'html_datetime');
  $variables['title'] = $node->getTitle();
  $variables['image_url'] = 'http://richardbuchanan.com/sites/richardbuchanan.com/themes/custom/rcb/images/about.png';
  $variables['image_height'] = '390';
  $variables['image_width'] = '1215';

  if ($node->hasField('field_image')) {
    $image = $node->get('field_image')->getValue();

    if ($image) {
      $variables['image_url'] = file_create_url($node->field_image->entity->getFileUri());
      $variables['image_height'] = $image[0]['height'];
      $variables['image_width'] = $image[0]['width'];
    }
  }
}
