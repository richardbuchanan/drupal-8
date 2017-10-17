<?php

namespace Drupal\bdg_custom\Plugin\Block;

use Drupal\Core\Block\BlockBase;

/**
 * Provides a 'Copyright' Block.
 *
 * @Block(
 *   id = "copyright_block",
 *   admin_label = @Translation("Copyright block"),
 *   category = @Translation("Copyright"),
 * )
 */
class CopyrightBlock extends BlockBase {

  /**
   * {@inheritdoc}
   */
  public function build() {
    $dates = '2013-' . date('Y');
    $markup = $this->t('<div class="uk-margin-small-bottom">&copy; @dates Buchanan Design Group</div>', array('@dates' => $dates));

    return array(
      '#markup' => $markup,
    );
  }

}
