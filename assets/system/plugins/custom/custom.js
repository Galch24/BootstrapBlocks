function watchForNavbar() {

  var width = $('#header').innerWidth();
  if (width <= 768) {
    $('.navbar-nav').each(function () {
      $(this).removeClass('drophover');
    });
    
    if ($('#main-menu').hasClass('in')) {
      $('#close-main-navbar').removeClass('hidden');
    } else {
      $('#close-main-navbar').addClass('hidden');
    }
  } else {
    $('.navbar-nav').each(function () {
      $(this).addClass('drophover');
    });
  }
}

(function ($) {

  $(document).ready(function() {

    /* Доработка dropdown ссылок, чтобы при клике на dropdown внутри 
     * раскрывшийся пункт не закрывался.
     */    
    $('ul.dropdown-menu [data-toggle=dropdown]').on('click', function(event) {
        // Avoid following the href location when clicking
        event.preventDefault(); 
        // Avoid having the menu to close when clicking
        event.stopPropagation(); 
        // If a menu is already open we close it
        if ($('ul.dropdown-menu [data-toggle=dropdown]').parent().hasClass('open')) {
          $('ul.dropdown-menu [data-toggle=dropdown]').parent().removeClass('open');
        } else {
          // opening the one you clicked on
          $(this).parent().addClass('open');
        }
    });
    // Конец доработки dropdown ссылок.
    
    //При изменении размера окна браузера включаем/отключаем поведение меню на hover
    $(window).resize(watchForNavbar);
    $(window).load(watchForNavbar);

    
    // Showing dropdown content on hover
    $('.drophover .dropdown-toggle').on({
      mouseenter: function () {
        //console.log('mouseenter = ' + $(this).parent().parent().attr('class'));
        if ((!$(this).parent().hasClass('open')) 
              && (!$(this).parent().hasClass('submenu'))
              && ($(this).parent().parent().hasClass('drophover'))) {
          $(this).trigger('click');
          
        }
      },
    });
     $('.drophover li.dropdown').on({
      mouseleave: function () {
        // Submenu must stay opened
        if ((!$(this).hasClass('submenu')) && ($(this).parent().hasClass('drophover'))) {
          $('.dropdown-toggle', this).trigger('click');
          //console.log('mouseleave = ' + $(this).parent().attr('class'));
        }
      },
    });
    //end of Showing dropdown content on hover
    
    // Display close-button for #main-menu when it's open
    $('#main-menu').on('hide.bs.collapse', function () {
      $('#close-main-navbar').addClass('hidden');
    });
    $('#main-menu').on('show.bs.collapse', function () {
      $('#close-main-navbar').removeClass('hidden');
    });
    
    
    //Close .navbar after user-menu opening
    $('#top-bar .dropdown').on('show.bs.dropdown', function () {
      if ($('#main-menu').hasClass('in')) {
        $('#main-menu').removeClass('in');
        $('#close-main-navbar').addClass('hidden');
      }
    })
  });

})(window.jQuery);
