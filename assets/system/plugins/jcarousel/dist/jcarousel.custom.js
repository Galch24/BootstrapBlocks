(function($) {
    $(function() {
      
      /*
      Carousel initialization
      */
      $('.jcarov')
         .jcarousel({
            // Options go here
            vertical: true,
            wrap: 'circular',
      });

      /*
       Prev control initialization
       */
      $('.jcarov-prev')
          .on('jcarouselcontrol:active', function() {
              $(this).removeClass('inactive');
          })
          .on('jcarouselcontrol:inactive', function() {
              $(this).addClass('inactive');
          })
          .jcarouselControl({
              // Options go here
              target: '-=1'
          });

      /*
       Next control initialization
       */
      $('.jcarov-next')
          .on('jcarouselcontrol:active', function() {
              $(this).removeClass('inactive');
          })
          .on('jcarouselcontrol:inactive', function() {
              $(this).addClass('inactive');
          })
          .jcarouselControl({
              // Options go here
              target: '+=1'
          });

      /*
       Pagination initialization
       */
      $('.jcarov-pagination')
          .on('jcarouselpagination:active', 'a', function() {
              $(this).addClass('active');
          })
          .on('jcarouselpagination:inactive', 'a', function() {
              $(this).removeClass('active');
          })
          .jcarouselPagination({
              // Options go here
          });
          

          
          
    });
})(jQuery);
