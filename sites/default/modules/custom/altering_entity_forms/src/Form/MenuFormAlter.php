<?php

namespace Drupal\altering_entity_forms\Form;

use Drupal\Core\Form\FormStateInterface;
use Drupal\menu_ui\MenuForm;

/**
 * Base form for menu edit forms.
 */
class MenuFormAlter extends MenuForm {

  /**
   * {@inheritdoc}
   */
  public function form(array $form, FormStateInterface $form_state) {
    $menu = $this->entity;

    $form = parent::form($form, $form_state);

    return $form;
  }

  /**
   * {@inheritdoc}
   */
  public function submitForm(array &$form, FormStateInterface $form_state) {
    parent::submitForm($form, $form_state);

    ksm($form);
  }

}
