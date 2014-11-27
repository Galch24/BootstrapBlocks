"use strict" #jshint
module.exports = (grunt) ->
  grunt.initConfig
    jshint:
      options:
        jshintrc: ".jshintrc" #jshint config file

      all: ["Gruntfile.js", "assets/js/*.js", "!assets/js/scripts.min.js"]

    less:
      all:
        files:
          "assets/css/style.min.css": "assets/system/less/style.less"

    concat:
      all:
        files:
         "assets/js/scripts.min.js": [
              "assets/system/plugins/bootstrap/js/transition.js", 
              "assets/system/plugins/bootstrap/js/alert.js", 
              "assets/system/plugins/bootstrap/js/button.js", 
              "assets/system/plugins/bootstrap/js/carousel.js", 
              "assets/system/plugins/bootstrap/js/collapse.js", 
              "assets/system/plugins/bootstrap/js/dropdown.js", 
              "assets/system/plugins/bootstrap/js/modal.js", 
              "assets/system/plugins/bootstrap/js/tooltip.js", 
              "assets/system/plugins/bootstrap/js/popover.js", 
              "assets/system/plugins/bootstrap/js/scrollspy.js", 
              "assets/system/plugins/bootstrap/js/tab.js",
              "assets/system/plugins/bootstrap-select/js/bootstrap-select.js",
              "assets/system/plugins/bootstrap-select/js/bootstrap-select.custom.js",
              "!assets/system/plugins/custom/custom.js",
              "assets/system/plugins/*.js"]

    uglify:
      all:
        files:
          "assets/js/scripts.min.js": [
              "assets/system/plugins/bootstrap/js/transition.js", 
              "assets/system/plugins/bootstrap/js/alert.js", 
              "assets/system/plugins/bootstrap/js/button.js", 
              "assets/system/plugins/bootstrap/js/carousel.js", 
              "assets/system/plugins/bootstrap/js/collapse.js", 
              "assets/system/plugins/bootstrap/js/dropdown.js", 
              "assets/system/plugins/bootstrap/js/modal.js", 
              "assets/system/plugins/bootstrap/js/tooltip.js", 
              "assets/system/plugins/bootstrap/js/popover.js", 
              "assets/system/plugins/bootstrap/js/scrollspy.js", 
              "assets/system/plugins/bootstrap/js/tab.js",
              "assets/system/plugins/bootstrap-select/js/bootstrap-select.js",
              "assets/system/plugins/bootstrap-select/js/bootstrap-select.custom.js",
              "!assets/system/plugins/custom/custom.js",
              "assets/system/plugins/*.js"]

    watch:
      less:
        files: ["assets/system/less/*.less", 
              "assets/system/less/common/*.less",
              "assets/system/less/common/core/*.less",
              "assets/system/less/libs/*.less",
              "assets/system/less/libs/bootstrap-select/*.less",
              "assets/system/less/common/modules/*.less",
              "assets/system/less/common/regions/*.less",
              ]
        tasks: ["less"]

      js:
        files: ["<%= jshint.all %>"]
        tasks: ["jshint", "uglify"]

    clean:
      dist: ["assets/css/style.min.css", "assets/js/scripts.min.js"]

  grunt.loadNpmTasks "grunt-contrib-clean"
  grunt.loadNpmTasks "grunt-contrib-jshint"
  grunt.loadNpmTasks "grunt-contrib-uglify"
  grunt.loadNpmTasks "grunt-contrib-concat"
  grunt.loadNpmTasks "grunt-contrib-watch"
  grunt.loadNpmTasks "grunt-contrib-less"
  grunt.registerTask "default", ["clean", "less", "concat"]
  grunt.registerTask "build", ["clean", "less", "uglify"]
  grunt.registerTask "dev", ["watch"]