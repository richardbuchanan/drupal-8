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

  Drupal.behaviors.rcbFootnotes = {
    attach: function(context, settings) {
      $(document).click(function (e) {
        var $target = e.target;
        var $footnote_reference = $($target).hasClass('footnote-reference');

        if (!$footnote_reference) {
          $('.node--references li').each(function () {
            $(this).removeClass('focused')
          })
        }
      });

      $('[rcb-footnote-popup]').each(function () {
        var $id = $(this).attr('rcb-footnote-popup');
        var $sup = $(context).find('sup[rcb-footnote-id="' + $id + '"]');
        $(this).insertAfter($sup);
      });

      $('sup[rcb-footnote-id]').click(function () {
        var $id = $(this).attr('rcb-footnote-id').replace('footnoteref', 'footnote');
        $('.node--references').find('#' + $id).addClass('focused');
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
