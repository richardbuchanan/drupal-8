/**
 * @file
 * Attaches behaviors for rcb.
 */

(function ($, Drupal) {

  'use strict';

  Drupal.behaviors.rcb = {
    attach: function () {
      $('pre code').each(function(i, block) {
        hljs.highlightBlock(block);
      });

      $(document).ready(function () {
        setMainHeight()
      });

      $(window).resize(function() {
        setMainHeight()
      });
    }
  };

  function getToolbarHeight() {
    var $body = $('body');
    var $toolbar = $('#toolbar-administration');
    var $navbarVisible = $('.uk-navbar-container:visible');
    var $toolbarHeight = 0;

    if ($toolbar.length) {
      $toolbarHeight = 40;
    }
    if ($body.hasClass('toolbar-horizontal') && $body.hasClass('toolbar-tray-open')) {
      $toolbarHeight = 79;
    }
    if ($navbarVisible) {
      var $navbar = $('.uk-navbar-container');
      $toolbarHeight += ($navbar.height() + 2)
    }

    return $toolbarHeight
  }

  function setMainHeight() {
    var $html = $('html');
    var $htmlHeight = $html.height();
    var $main = $('.rcb-main');
    var $mainHeight = $main.height();

    if ($mainHeight < $htmlHeight) {
      $main.height($htmlHeight - getToolbarHeight())
    }
  }
})(jQuery, Drupal);
