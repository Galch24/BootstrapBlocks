(function($) {
    $(function() {
        var jcarousel = $('.jcarousel-5');

        jcarousel
            .on('jcarousel:reload jcarousel:create', function () {
                var width = jcarousel.innerWidth();
                
                if (width >= 768) {
                  width = width / 5;
                } else if (width >= 450) {
                  width = width / 4;
                }
                else {
                  width = width / 2;
                }
                

                jcarousel.jcarousel('items').css('width', width + 'px');
            })
            .jcarousel({
                wrap: 'circular'
            });

        $('.prev-5')
            .jcarouselControl({
                target: '-=1'
            });

        $('.next-5')
            .jcarouselControl({
                target: '+=1'
            });

        $('.jcarousel-pagination-5')
            .on('jcarouselpagination:active', 'a', function() {
                $(this).addClass('active');
            })
            .on('jcarouselpagination:inactive', 'a', function() {
                $(this).removeClass('active');
            })
            .on('click', function(e) {
                e.preventDefault();
            })
            .jcarouselPagination({
                perPage: 1,
                item: function(page) {
                    return '<a href="#' + page + '">' + page + '</a>';
                }
            });
    });
})(jQuery);
