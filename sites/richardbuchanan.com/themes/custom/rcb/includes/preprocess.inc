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
use Drupal\taxonomy\Entity\Term;
use Drupal\Core\Template\Attribute;
use Drupal\rcb\RCB;
use Drupal\user\Entity\User;

/**
 * Implements template_preprocess_html().
 */
function rcb_preprocess_html(&$variables) {
  $current_path = \Drupal::service('path.current')->getPath();
  $user_login = $current_path == '/user' && \Drupal::currentUser()->isAnonymous();

  if ($current_path == '/user/login' || $current_path == '/user/password' || $user_login) {
    $noindex = [
      '#tag' => 'meta',
      '#attributes' => [
        'name' => 'robots',
        'content' => 'noindex, nofollow',
      ],
    ];

    $variables['#attached']['html_head'][] = [$noindex, 'meta_noindex'];
  }
}

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

  $comment_uid = $variables['comment']->getOwnerId();
  $comment_user = User::load($comment_uid);
  $variables['default_user_picture'] = FALSE;

  if ($comment_user->user_picture->isEmpty()) {
    $variables['default_user_picture'] = TRUE;
  }

  $title = $variables['title']->getGeneratedLink();
  $title = str_replace('class="permalink"', 'class="permalink uk-link-reset"', $title);
  $variables['title']->setGeneratedLink($title);
  $variables['content']['links']['#create_placeholder'] = FALSE;
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
 * Implements template_preprocess_image().
 */
function rcb_preprocess_image(&$variables) {
  $variables['attributes']['class'][] = 'rcb-thumbnail';
  $variables['attributes']['class'][] = 'uk-margin-small-bottom';
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

  $comment = $node->hasField('comment');
  $variables['comments_open'] = FALSE;

  if ($comment) {
    $comment_field_name = 'comment';
    $comments_open = $node->$comment_field_name->status == '2';

    if ($comments_open) {
      $variables['comments_open'] = TRUE;
      $comment_count = $node->$comment_field_name->comment_count;

      switch ($comment_count) {
        case '1':
          $variables['comment_count'] = "$comment_count comment";
          break;

        default:
          $variables['comment_count'] = "$comment_count comments";
      }
    }
  }

  $tags = $node->hasField('field_tags') ? $node->get('field_tags')->getValue() : [];
  $has_tags = FALSE;

  if ($tags) {
    $tags_field_name = 'field_tags';
    $has_tags = count($node->$tags_field_name->getValue()) ? TRUE : FALSE;
  }

  $variables['has_tags'] = $has_tags;

  $timestamp = $node->getCreatedTime();
  $variables['date'] = \Drupal::service('date.formatter')->format($timestamp, 'custom', 'F j, Y');
  $variables['created'] = \Drupal::service('date.formatter')->format($timestamp, 'html_datetime');
  $variables['modified'] = \Drupal::service('date.formatter')->format($timestamp, 'html_datetime');
  $variables['title'] = $node->getTitle();

  $variables['image_default'] = FALSE;
  $variables['image_url'] = 'https://richardbuchanan.com/sites/richardbuchanan.com/themes/custom/rcb/images/about.png';
  $variables['image_height'] = '390';
  $variables['image_width'] = '1215';

  $blog_post = $node->getType() == 'blog_post';
  $default_images_directory = '/sites/richardbuchanan.com/files/default-images/';
  $image = $node->hasField('field_image') ? $node->get('field_image')->getValue() : [];

  if ($image) {
    $variables['image_url'] = file_create_url($node->field_image->entity->getFileUri());
    $variables['image_height'] = $image[0]['height'];
    $variables['image_width'] = $image[0]['width'];
  }
  elseif ($blog_post) {
    $path = 'https://richardbuchanan.com' . $default_images_directory . 'rcb-blog.png';
    $variables['image_url'] = file_create_url($path);
    $variables['image_height'] = 219;
    $variables['image_width'] = 651;
  }
  elseif ($tags) {
    $terms = [];

    foreach ($tags as $tag) {
      $tid = $tag['target_id'];
      $term = Term::load($tid);
      $term_name = strtolower($term->getName());
      $term_name = str_replace(' ', '-', $term_name);
      $terms[] = $term_name;
    }

    $filename = implode('-', $terms);
    $height = 0;
    $width = 0;

    switch ($filename) {
      case 'drupal-7-uikit-2':
      case 'drupal-7-uikit-3':
      case 'drupal-8-uikit-2':
      case 'drupal-8-uikit-3':
        $filename = "$filename.png";
        $height = 260;
        $width = 1900;
        break;

      case 'drupal-uikit':
        $filename = 'uikit-for-drupal.png';
        $height = 320;
        $width = 1900;
        break;

      default:
        $filename = FALSE;
    }

    if ($filename) {
      $path = $default_images_directory . $filename;
      $file_exists = file_exists(DRUPAL_ROOT . $path);

      if ($file_exists) {
        $variables['image_default'] = TRUE;
        $variables['image_url'] = file_create_url($path);
        $variables['image_height'] = $height;
        $variables['image_width'] = $width;
      }
    }
  }

  $variables['main_attributes'] = new Attribute;
  $variables['main_attributes']->setAttribute('id', 'node--main-content');
}
