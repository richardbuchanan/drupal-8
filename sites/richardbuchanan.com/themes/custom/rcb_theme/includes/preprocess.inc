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

use Drupal\Core\Link;
use Drupal\Core\Render\Markup;
use Drupal\Core\StringTranslation\TranslatableMarkup;
use Drupal\Core\Template\Attribute;
use Drupal\Core\Url;
use Drupal\block\Entity\Block;
use Drupal\rcb_theme\RCBNodeImage;
use Drupal\uikit\UIkit;

/**
 * Implements template_preprocess_html().
 */
function rcb_theme_preprocess_html(&$variables) {
  global $base_url;
  $rcb_theme = drupal_get_path('theme', 'rcb_theme');
  $site_logo = $base_url . '/' . $rcb_theme . '/logo.png';

  $schema_organization = '{' . "\n";
  $schema_organization .= '  "@context": "http://schema.org",' . "\n";
  $schema_organization .= '  "@type": "Organization",' . "\n";
  $schema_organization .= '  "url": "' . $base_url . '",' . "\n";
  $schema_organization .= '  "logo": "' . $site_logo . '",' . "\n";
  $schema_organization .= '  "sameAs": "https://www.facebook.com/Richard.C.Buchanan.III",' . "\n";
  $schema_organization .= '  "sameAs": "https://plus.google.com/+RichardBuckBuchanan",' . "\n";
  $schema_organization .= '  "sameAs": "https://www.linkedin.com/in/houseofcanon/",' . "\n";
  $schema_organization .= '  "sameAs": "https://twitter.com/HouseOfCanon",' . "\n";
  $schema_organization .= '  "sameAs": "http://www.youtube.com/c/RichardBuckBuchanan"' . "\n";
  $schema_organization .= '}';
  $variables['schema_organization'] = Markup::create($schema_organization);
}

/**
 * Implements template_preprocess_page().
 */
function rcb_theme_preprocess_page(&$variables) {
  global $base_url;
  $rcb_theme = drupal_get_path('theme', 'rcb_theme');
  $site_logo = $base_url . '/' . $rcb_theme . '/logo.png';

  $variables['base_url'] = $base_url;
  $variables['site_logo'] = $site_logo;
  $variables['facebook'] = 'https://www.facebook.com/Richard.C.Buchanan.III';
  $variables['google_plus'] = 'https://plus.google.com/+RichardBuckBuchanan';
  $variables['linkedin'] = 'https://www.linkedin.com/in/houseofcanon';
  $variables['twitter'] = 'https://twitter.com/HouseOfCanon';
  $variables['youtube'] = 'http://www.youtube.com/c/RichardBuckBuchanan';

  $variables['header_attributes']['class'] = ['uk-hidden@m'];
  $variables['page_attributes']['class'] = [
    'uk-container',
    'uk-container-expand',
    'uk-position-relative',
  ];
  $variables['content_attributes']['class'] = ['uk-width-expand'];
  $variables['sidebar_first_attributes']['class'] = [
    'uk-visible@m',
    'uk-width-medium',
  ];
  $variables['sidebar_second_attributes']['class'] = [
    'uk-visible@l',
    'uk-width-medium',
  ];
  $variables['footer_attributes'] = new Attribute;
  $variables['footer_attributes']->setAttribute('id', 'page--footer');
  $variables['footer_attributes']->addClass('uk-container');
  $variables['footer_attributes']->addClass('uk-container-expand');
  $variables['footer_attributes']->setAttribute('role', 'contentinfo');

  $node = isset($variables['node']) ? $variables['node'] : FALSE;
  $fid = $node && isset($node->field_image->entity) ? $node->field_image->entity->id() : NULL;
  $variables['node_image'] = RCBNodeImage::buildResponsiveImage($fid, 'wide');
  $variables['page_title'] = [];
  $variables['breadcrumb'] = [];

  if (!empty($variables['node_image'])) {
    $request = \Drupal::request();
    $route_match = \Drupal::routeMatch();
    $variables['page_title'] = \Drupal::service('title_resolver')->getTitle($request, $route_match->getRouteObject());
    $variables['content_attributes']['class'][] = 'page-title-hidden';

    if (!empty($variables['page']['content']['rcb_theme_breadcrumbs']) && ! \Drupal::service('path.matcher')->isFrontPage()) {
      $breadcrumb_block = \Drupal\block\BlockViewBuilder::lazyBuilder('rcb_theme_breadcrumbs', 'full');
      $variables['breadcrumb'] = \Drupal::service('renderer')->renderPlain($breadcrumb_block);
      $variables['content_attributes']['class'][] = 'page-breadcrumb-hidden';
    }
  }
}

/**
 * Implements template_preprocess_block().
 */
function rcb_theme_preprocess_block(&$variables) {
  $base_plugin_id = $variables['base_plugin_id'];
  $book_navigation = $base_plugin_id == 'book_navigation';
  $block = Block::load($variables['elements']['#id']);
  $region = $block->getRegion();

  if ($book_navigation) {
    switch ($region) {
      case 'offcanvas':
        foreach ($variables['content'] as $key => $content) {
          if (is_array($content) && isset($content['#theme'])) {
            $variables['content'][$key]['#theme'] = 'book_tree__offcanvas';
          }
        }
        break;

      case 'sidebar_first':
      case 'sidebar_second':
        foreach ($variables['content'] as $key => $content) {
          if (is_array($content) && isset($content['#theme'])) {
            $variables['content'][$key]['#theme'] = 'book_tree__sidebar';
          }
        }
        break;
    }
  }
}

/**
 * Implements template_preprocess_breadcrumb().
 */
function rcb_theme_preprocess_breadcrumb(&$variables) {
  global $base_url;

  foreach ($variables['breadcrumb'] as $key => $item) {
    $variables['breadcrumb'][$key]['attributes'] = new Attribute;
    $variables['breadcrumb'][$key]['list_attributes'] = new Attribute;
    $variables['breadcrumb'][$key]['text_attributes'] = new Attribute;
    $text = is_object($variables['breadcrumb'][$key]['text']) ? $variables['breadcrumb'][$key]['text']->getUntranslatedString() : $variables['breadcrumb'][$key]['text'];

    if ($variables['breadcrumb'][$key]['url']) {
      if ($text == 'Home') {
        $variables['breadcrumb'][$key]['attributes']->setAttribute('href', $base_url);
      }
      else {
        $variables['breadcrumb'][$key]['attributes']->setAttribute('href', $variables['breadcrumb'][$key]['url']);
      }
    }

    if ($text == 'Home') {
      $site_name = \Drupal::config('system.site')->get('name');
      $home = '<span class="uk-hidden">' . $site_name . '</span>';
      $text = new TranslatableMarkup($home);
      $variables['breadcrumb'][$key]['text'] = $text;
      $variables['breadcrumb'][$key]['attributes']->addClass('uk-icon');
      $variables['breadcrumb'][$key]['attributes']->setAttribute('title', t('Home'));
      $variables['breadcrumb'][$key]['attributes']->setAttribute('uk-icon', 'icon: home; ratio: 0.9');
      $variables['breadcrumb'][$key]['attributes']->setAttribute('uk-tooltip', '');
    }

    $variables['breadcrumb'][$key]['attributes']->setAttribute('property', 'item');
    $variables['breadcrumb'][$key]['attributes']->setAttribute('typeof', 'WebPage');
    $variables['breadcrumb'][$key]['list_attributes']->setAttribute('property', 'itemListElement');
    $variables['breadcrumb'][$key]['list_attributes']->setAttribute('typeof', 'ListItem');
    $variables['breadcrumb'][$key]['text_attributes']->setAttribute('property', 'name');
  }
}

/**
 * Implements template_preprocess_comment().
 */
function rcb_theme_preprocess_comment(&$variables) {
  $comment = $variables['comment'];
  $comment_number = $variables['elements']['#weight'] + 1;
  $timestamp = $comment->getCreatedTime();
  $title = $comment->getSubject();
  $permalink_title = Markup::create('#');

  $date = '<span>' . \Drupal::service('date.formatter')->format($timestamp, 'short') . '</span>';
  $date = Markup::create($date);
  $variables['date'] = $date;

  if (isset($comment->in_preview)) {
    $uri = new Url('<front>');
    $permalink_uri = new Url('<front>');
  }
  else {
    $link_icon = '<span class="uk-hidden-hover uk-margin-small-left uk-text-muted" uk-icon="icon: link"></span>';
    $title = Markup::create($comment->getSubject() . $link_icon);
    $uri = $comment->permalink();
    $attributes = $uri->getOption('attributes') ? : [];
    $attributes += ['class' => [
      'permalink',
      'uk-link-reset',
      'uk-visible-toggle',
    ], 'rel' => 'bookmark'];
    $uri->setOption('attributes', $attributes);
    $permalink_uri = $comment->permalink();
    $permalink_title = Markup::create('# ' . $comment_number);
  }

  $variables['title'] = Link::fromTextAndUrl($title, $uri);
  $variables['permalink'] = Link::fromTextAndUrl($permalink_title, $permalink_uri);
  $variables['placeholder_avatar'] = '/sites/richardbuchanan.com/files/pictures/placeholder_avatar.svg';
}

/**
 * Implements template_preprocess_container().
 */
function rcb_theme_preprocess_container(&$variables) {
  $type = $variables['element']['#type'];

  switch ($type) {
    case 'actions':
      $variables['attributes']['class'][] = 'uk-margin';
  }
}

/**
 * Implements template_preprocess_field().
 */
function rcb_theme_preprocess_field(&$variables) {
  $field_name = $variables['field_name'];

  if ($field_name == 'uid') {
    foreach ($variables['items'] as $key => $item) {
      $variables['items'][$key]['content']['#theme'] = 'username__node';
    }
  }

  if ($field_name == 'comment') {
    $variables['attributes']['id'] = 'comments';
  }
}

/**
 * Implements template_preprocess_form().
 */
function rcb_theme_preprocess_form(&$variables) {
  global $base_url;
  $form_id = $variables['element']['#form_id'];

  switch ($form_id) {
    case 'search_form':
      $variables['layout'] = 'horizontal';
      break;

    case 'search_block_form':
      $variables['base_url'] = $base_url;
      $variables['attributes']['itemprop'] = 'potentialAction';
      $variables['attributes']['itemscope'] = '';
      $variables['attributes']['itemtype'] = 'http://schema.org/SearchAction';
      break;

    default:
      $variables['layout'] = 'stacked';
  }
}

/**
 * Implements template_preprocess_form_element().
 */
function rcb_theme_preprocess_form_element(&$variables) {
  $element = $variables['element'];
  $type = $element['#type'];

  $form_advanced = $type == 'checkbox' || $type == 'radio';
  if ($form_advanced) {
    $variables['label_text'] = $variables['label']['#title'];
  }
}

/**
 * Implements template_preprocess_input().
 */
function rcb_theme_preprocess_input(&$variables) {
  global $base_url;
  $type = $variables['element']['#type'];
  $variables['search_query_string'] = FALSE;

  if ($type == 'submit') {
    $variables['button_icon'] = FALSE;

    if (isset($variables['element']['#icon'])) {
      $icon = $variables['element']['#icon'];
      $variables['attributes']['class'][] = 'uk-button-text';
      $variables['attributes']['uk-icon'] = "icon: $icon";
      $variables['button_icon'] = TRUE;
    }
    else {
      $value = $variables['element']['#value']->__toString();
      switch ($value) {
        case 'Advanced search':
        case 'Log in':
        case 'Preview':
        case 'Save':
        case 'Search':
        case 'Send message':
        case 'Submit':
          $variables['attributes']['class'][] = 'uk-button-primary';
          break;

        default:
          $variables['attributes']['class'][] = 'uk-button-default';
      }
    }
  }
  elseif ($type == 'search') {
    $parents_count = count($variables['element']['#array_parents']);

    if ($parents_count == 1) {
      $variables['search_query_string'] = $base_url . '/search/content?keys={keys}';
      $variables['attributes']['itemprop'] = 'query-input';
      $variables['attributes']['required'] = '';
      unset($variables['attributes']['maxlength']);

      $value_empty = isset($variables['attributes']['value']) && empty($variables['attributes']['value']);
      if ($value_empty) {
        unset($variables['attributes']['value']);
      }
    }
  }
}

/**
 * Implements template_preprocess_links() for links--comment.html.twig.
 */
function rcb_theme_preprocess_links__comment(&$variables) {
  $new_links = [];

  if (!empty($variables['links'])) {
    $links = $variables['links'];

    if (isset($links['comment-reply'])) {
      $new_links['comment-reply'] = $links['comment-reply'];
    }
    if (isset($links['comment-edit'])) {
      $new_links['comment-edit'] = $links['comment-edit'];
    }
    if (isset($links['comment-delete'])) {
      $new_links['comment-delete'] = $links['comment-delete'];
    }
    if (isset($links['comment-approve'])) {
      $new_links['comment-approve'] = $links['comment-approve'];
    }
  }

  $variables['links'] = $new_links;
}

/**
 * Implements template_preprocess_links() for links--node.html.twig.
 */
function rcb_theme_preprocess_links__node(&$variables) {
  $variables['node_full'] = TRUE;

  if (isset($variables['links']['node-readmore'])) {
    $variables['links']['node-readmore']['attributes'] = new Attribute;
    $variables['links']['node-readmore']['attributes']->addClass('node--readmore');
    $title = $variables['links']['node-readmore']['link']['#title']->__toString();
    $title = '<span class="uk-margin-small-right" uk-icon="icon: more"></span>' . $title;
    $title = new TranslatableMarkup($title);
    $variables['links']['node-readmore']['link']['#title'] = $title;
    $variables['node_full'] = FALSE;
  }
  if (isset($variables['links']['comment-add'])) {
    $variables['links']['comment-add']['attributes'] = new Attribute;
    $variables['links']['comment-add']['attributes']->addClass('node--comment-add');
    $title = $variables['links']['comment-add']['link']['#title']->__toString();
    $title = '<span class="uk-margin-small-right" uk-icon="icon: comment"></span>' . $title;
    $title = new TranslatableMarkup($title);
    $variables['links']['comment-add']['link']['#title'] = $title;
  }
}

/**
 * Implements template_preprocess_menu().
 */
function rcb_theme_preprocess_menu(&$variables) {
  $menu_name = $variables['menu_name'];
  $variables['attributes']['class'][] = 'menu';
  $variables['attributes']['class'][] = 'menu--' . str_replace('_', '-', $menu_name);

  switch ($menu_name) {
    case 'footer':
      $variables['attributes']['class'][] = 'uk-subnav';
  }
}

/**
 * Implements template_preprocess_node().
 */
function rcb_theme_preprocess_node(&$variables) {
  global $base_url;
  $node = $variables['node'];

  $timestamp = $node->getCreatedTime();
  $date = '<span><span class="uk-margin-small-right" uk-icon="icon: calendar"></span>';
  $date .= \Drupal::service('date.formatter')->format($timestamp, 'short') . '</span>';
  $date = Markup::create($date);
  $variables['date'] = $date;

  $site_name = \Drupal::config('system.site')->get('name');
  $node_url = $node->urlInfo()->toString();
  $author = $site_name;
  $date_published = \Drupal::service('date.formatter')->format($timestamp, 'html_datetime', '', 'UTC');
  $logo = UIkit::getThemeSetting('logo');
  $logo_url = str_replace('.svg', '.png', $base_url . $logo['url']);
  $modified_timestamp = $node->getChangedTime();
  $date_modified = \Drupal::service('date.formatter')->format($modified_timestamp, 'html_datetime', '', 'UTC');
  $node_image_fid = $node && isset($node->field_image->entity) ? $node->field_image->entity->id() : NULL;
  $node_image_url = $base_url . '/' . drupal_get_path('theme', 'rcb_theme') . '/images/default-image.png';
  $node_image_height = '533';
  $node_image_width = '1025';
  $about = $variables['attributes']['about'];

  $variables['attributes']['typeof'] = 'schema:Article';
  $variables['attributes']['about'] = $base_url . $about;

  if ($variables['display_submitted']) {
    $author = $node->getOwner()->getDisplayName();
  }
  if ($node_image_fid) {
    $node_image_uri = $node->field_image->entity->getFileUri();
    $node_image_url = file_create_url($node_image_uri);
    $image_field = $node->field_image;
    $image_view = $image_field->view();
    $image_properties = $image_view[0]['#item']->getProperties();
    $node_image_height = $image_properties['height']->getValue();
    $node_image_width = $image_properties['width']->getValue();
  }

  $structured_data = '<span class="hidden" property="schema:mainEntityOfPage"  typeof="schema:WebPage" content="' . $base_url . $node_url . '"></span>';
  $structured_data .= '<span class="hidden" property="schema:author" content="' . $author . '"></span>';

  $structured_data .= '<span class="hidden" property="schema:datePublished" content="' . $date_published . '"></span>';
  $structured_data .= '<span class="hidden" property="schema:dateModified" content="' . $date_modified . '"></span>';

  $structured_data .= '<div class="hidden" property="schema:publisher" typeof="schema:Organization">';

  $structured_data .= '<div property="schema:logo" typeof="schema:ImageObject">';
  $structured_data .= '<img src="' . $logo_url . '" />';
  $structured_data .= '<span property="schema:url" content="' . $logo_url . '">' . $logo_url . '</span>';
  $structured_data .= '<span property="schema:height" content="57"></span>';
  $structured_data .= '<span property="schema:width" content="47"></span>';
  $structured_data .= '</div>';

  $structured_data .= '<span property="schema:name" content="' . $site_name . '"></span>';
  $structured_data .= '</div>';

  $structured_data .= '<div class="hidden" property="schema:image" typeof="schema:ImageObject">';
  $structured_data .= '<img src="' . $node_image_url . '" />';
  $structured_data .= '<span property="schema:url" content="' . $node_image_url . '"></span>';
  $structured_data .= '<span property="schema:height" content="' . $node_image_height . '"></span>';
  $structured_data .= '<span property="schema:width" content="' . $node_image_width . '"></span>';
  $structured_data .= '</div>';

  $variables['structured_data'] = new TranslatableMarkup($structured_data);

  // https://search.google.com/structured-data/testing-tool
  // https://developers.google.com/search/docs/data-types/sitename
}

function rcb_theme_preprocess_field__node__title(&$variables) {
  foreach ($variables['items'] as $key => $item) {
    $variables['items'][$key]['attributes']->removeAttribute('property');
  }

  if (isset($variables['attributes']['property'])) {
    unset($variables['attributes']['property']);
  }
}

/**
 * Implements template_preprocess_user().
 */
function rcb_theme_preprocess_user(&$variables) {
  if ($variables['content']['member_for']) {
    $created = $variables['elements']['#user']->getCreatedTime();
    $member_for = \Drupal::service('date.formatter')
      ->formatInterval(\Drupal::time()->getRequestTime() - $created);
    $variables['content']['member_for']['#markup'] = t('<p><strong>Member for</strong> @member_for</p>', ['@member_for' => $member_for]);
  }
}

/**
 * Implements template_preprocess_username().
 */
function rcb_theme_preprocess_username(&$variables) {
  global $base_url;
  $about = isset($variables['attributes']['about']) ? $variables['attributes']['about'] : FALSE;
  $href = isset($variables['attributes']['href']) ? $variables['attributes']['href'] : FALSE;

  if ($about) {
    $variables['attributes']['about'] = $base_url . $about;
  }

  if ($href) {
    $variables['attributes']['href'] = $base_url . $href;
  }
}
