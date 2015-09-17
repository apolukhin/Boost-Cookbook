function chapter_show_base(chapter) {
    $('#Chapter01').hide();
    $('#Chapter02').hide();
    $('#Chapter03').hide();
    $('#Chapter04').hide();
    $('#Chapter05').hide();
    $('#Chapter06').hide();
    $('#Chapter07').hide();
    $('#Chapter08').hide();
    $('#Chapter09').hide();
    $('#Chapter10').hide();
    $('#Chapter11').hide();
    $('#Chapter12').hide();

    $('#Chapter' + chapter).show();
    var num = parseInt(chapter);
    num = num - 1;
    num = num + "";
    if (num.length < 2) {
        num = '0' + num;
    }

    return num;
}

function chapter_show(chapter) {
    window.location = '#Chapter' + chapter_show_base(chapter) + "_ref";
}

var editor = (function() {
    var content = [
        {
            "chapter":  "Chapter01",
            "title":    "Getting configuration options",
            "source":   ['Chapter01/program_options_base/main.cpp', 'Chapter01/program_options_short/cpp.main'],
            "compile":  "-lboost_program_options",
            "run":      "--apples=10 --oranges=5",
        }, {
            "chapter":  "Chapter01",
            "title":    "Storing any value in a container/variable",
            "source":   ['Chapter01/any/main.cpp'],
        }, {
            "chapter":  "Chapter01",
            "title":    "Storing multiple chosen types in a variable/container",
            "source":   ['Chapter01/variant/main.cpp'],
        }, {
            "chapter":  "Chapter01",
            "title":    "Using a safer way to work with a container that stores multiple chosen types",
            "source":   ['Chapter01/any_db_example/main.cpp', 'Chapter01/variant_db_example/main.cpp'],
        }, {
            "chapter":  "Chapter01",
            "title":    "Returning a value or flag where there is no value",
            "source":   [''],
        }, {
            "chapter":  "Chapter01",
            "title":    "Returning an array from a function",
            "source":   ['Chapter01/array/main.cpp'],
        }, {
            "chapter":  "Chapter01",
            "title":    "Combining multiple values into one",
            "source":   ['Chapter01/tuple/main.cpp'],
        }, {
            "chapter":  "Chapter01",
            "title":    "Reordering the parameters of function",
            "source":   ['Chapter01/bind_placeholders/main.cpp'],
        }, {
            "title":    "Binding a value as a function parameter",
            "chapter":  "Chapter01",
            "source":   ['Chapter01/bind_values/main.cpp'],
        }, {
            "title":    "Using the C++11 move emulation",
            "chapter":  "Chapter01",
            "source":   ['Chapter01/move/main.cpp'],
        }, {
            "title":    "Making a noncopyable class",
            "chapter":  "Chapter01",
            "source":   ['Chapter01/noncopyable/main.cpp'],
        }, {
            "title":    "Making a noncopyable but movable class",
            "chapter":  "Chapter01",
            "source":   ['Chapter01/noncopyable_movable/main.cpp'],
        },



        {
            "title":    "Converting strings to numbers",
            "chapter":  "Chapter02",
            "source":   ['Chapter02/lexical_to_number/main.cpp'],
        }, {
            "title":    "Converting numbers to strings",
            "chapter":  "Chapter02",
            "source":   ['Chapter02/lexical_to_string/main.cpp'],
        }, {
            "title":    "Converting numbers to numbers",
            "chapter":  "Chapter02",
            "source":   ['Chapter02/numeric_cast/main.cpp'],
        }, {
            "title":    "Converting user-defined types to/from strings",
            "chapter":  "Chapter02",
            "source":   ['Chapter02/lexical_user_defined/main.cpp'],
        }, {
            "title":    "Casting polymorphic objects",
            "chapter":  "Chapter02",
            "source":   ['Chapter02/polymorphic_cast/main.cpp'],
        }, {
            "title":    "Parsing simple input",
            "chapter":  "Chapter02",
            "source":   ['Chapter02/spirit/main.cpp'],
        }, {
            "title":    "Parsing input",
            "chapter":  "Chapter02",
            "source":   ['Chapter02/spirit_rules/main.cpp'],
        },



        {
            "title":    "Managing pointers to classes that do not leave scope",
            "chapter":  "Chapter03",
            "source":   ['Chapter03/scoped_ptr/main.cpp'],
        }, {
            "title":    "Reference counting of pointers to classes used across methods",
            "chapter":  "Chapter03",
            "source":   ['Chapter03/shared_ptr/main.cpp'],
            "compile":  "-lboost_thread -lboost_system",
        }, {
            "title":    "Managing pointers to arrays that do not leave scope",
            "chapter":  "Chapter03",
            "source":   ['Chapter03/scoped_array/main.cpp'],
        }, {
            "title":    "Reference counting pointers to arrays used across methods",
            "chapter":  "Chapter03",
            "source":   ['Chapter03/shared_array/main.cpp'],
            "compile":  "-lboost_thread -lboost_system",
        }, {
            "title":    "Storing any functional objects in a variable",
            "chapter":  "Chapter03",
            "source":   ['Chapter03/function_fobject/main.cpp', 'Chapter03/function_fpointer/main.cpp'],
        }, {
            "title":    "Passing C++11 lambda functions in a variable",
            "chapter":  "Chapter03",
            "source":   ['Chapter03/function_lambda_c++11/main.cpp'],
            "compile":  "-std=c++11",
        }, {
            "title":    "Containers of pointers",
            "chapter":  "Chapter03",
            "source":   ['Chapter03/ptr_container_c++11/main.cpp'],
            "compile":  "-std=c++11",
        }, {
            "title":    "Doing something at scope exit",
            "chapter":  "Chapter03",
            "source":   ['Chapter03/scope_exit/main.cpp'],
        }, {
            "title":    "Initializing the base class by a member of the derived class",
            "chapter":  "Chapter03",
            "source":   ['Chapter03/base_from_member/main.cpp'],
        },



        {
            "title":    "Checking sizes at compile time",
            "chapter":  "Chapter04",
            "source":   ['Chapter04/static_assert/main.cpp'],
        }, {
            "title":    "Enabling the usage of templated functions for integral types",
            "chapter":  "Chapter04",
            "source":   ['Chapter04/enable_if_c/main.cpp'],
        }, {
            "title":    "Disabling templated functions' usage for real types",
            "chapter":  "Chapter04",
            "source":   ['Chapter04/disable_if_c/main.cpp'],
        }, {
            "title":    "Creating a type from number",
            "chapter":  "Chapter04",
            "source":   ['Chapter04/mpl_int_/main.cpp'],
        }, {
            "title":    "Implementing a type trait",
            "chapter":  "Chapter04",
            "source":   ['Chapter04/is_stdvector/main.cpp'],
        }, {
            "title":    "Selecting an optimal operator for a template parameter",
            "chapter":  "Chapter04",
            "source":   ['Chapter04/conditional/main.cpp'],
        }, {
            "title":    "Getting a type of expression in C++03",
            "chapter":  "Chapter04",
            "source":   ['Chapter04/typeof/main.cpp'],
        },



        {
            "title":    "Creating an execution thread",
            "chapter":  "Chapter05",
            "source":   ['Chapter05/thread/main.cpp'],
            "compile":  "-lboost_thread -lboost_system",
        }, {
            "title":    "Syncing access to a common resource",
            "chapter":  "Chapter05",
            "source":   ['Chapter05/mutex/main.cpp'],
            "compile":  "-lboost_thread -lboost_system",
        }, {
            "title":    "Fast access to common resource using atomics",
            "chapter":  "Chapter05",
            "source":   ['Chapter05/atomics/main.cpp'],
            "compile":  "-lboost_thread -lboost_system",
        }, {
            "title":    "Creating a work_queue class",
            "chapter":  "Chapter05",            "chapter":  "Chapter08",
            "source":   ['Chapter05/work_queue/main.cpp'],
            "compile":  "-lboost_thread -lboost_system",
        }, {
            "title":    "Multiple-readers-single-writer lock",
            "chapter":  "Chapter05",
            "source":   ['Chapter05/shared_lock/main.cpp'],
            "compile":  "-lboost_thread -lboost_system",
        }, {
            "title":    "Creating variables that are unique per thread",
            "chapter":  "Chapter05",
            "source":   ['Chapter05/thread_specific_ptr/main.cpp'],
            "compile":  "-lboost_thread -lboost_system",
        }, {
            "title":    "Interrupting a thread",
            "chapter":  "Chapter05",
            "source":   ['Chapter05/interruptions/main.cpp'],
            "compile":  "-lboost_thread -lboost_system",
        }, {
            "title":    "Manipulating a group of threads",
            "chapter":  "Chapter05",
            "source":   ['Chapter05/thread_group/main.cpp'],
            "compile":  "-lboost_thread -lboost_system",
        },



        {
            "title":    "Registering a task for processing an arbitrary datatype",
            "chapter":  "Chapter06",
            "source":   ['Chapter06/tasks_processor_base/main.cpp', 'Chapter06/tasks_processor_base/tasks_processor_base.hpp'],
            "compile":  "-lboost_thread -lboost_system",
        }, 



        {
            "title":    "Changing cases and case-insensitive comparison",
            "chapter":  "Chapter07",
            "source":   ['Chapter07/case_conv/main.cpp'],
        }, {
            "title":    "Matching strings using regular expressions",
            "chapter":  "Chapter07",
            "source":   ['Chapter07/regex_match/main.cpp'],
            "compile":  "-lboost_regex",
        }, {
            "title":    "Searching and replacing strings using regular expressions",
            "chapter":  "Chapter07",
            "source":   ['Chapter07/regex_replace/main.cpp'],
            "compile":  "-lboost_regex",
        }, {
            "title":    "Formatting strings using safe printf-like functions",
            "chapter":  "Chapter07",
            "source":   ['Chapter07/format/main.cpp'],
        }, {
            "title":    "Replacing and erasing strings",
            "chapter":  "Chapter07",
            "source":   ['Chapter07/string_algo/main.cpp'],
        }, {
            "title":    "Representing a string with two iterators",
            "chapter":  "Chapter07",
            "source":   ['Chapter07/iterator_range/main.cpp'],
        }, {
            "title":    "Using a reference to string type",
            "chapter":  "Chapter07",
            "source":   ['Chapter07/string_ref/main.cpp'],
        },



        {
            "title":    'Using type "vector of types"',
            "chapter":  "Chapter08",
            "source":   ['Chapter08/vector_of_types/main.cpp'],
        }, {
            "title":    'Manipulating a vector of types',
            "chapter":  "Chapter08",
            "source":   ['Chapter08/manipulating_vector_of_types/main.cpp'],
        }, {
            "title":    "Getting a function's result type at compile time",
            "chapter":  "Chapter08",
            "source":   ['Chapter08/result_of_c++11/main.cpp'],
            "compile":  "-std=c++11",
        }, {
            "title":    "Making a higher-order metafunction",
            "chapter":  "Chapter08",
            "source":   ['Chapter08/higher_order_metafunctions/main.cpp'],
        }, {
            "title":    "Evaluating metafunctions lazily",
            "chapter":  "Chapter08",
            "source":   ['Chapter08/lazy/main.cpp'],
        }, {
            "title":    "Converting all the tuple elements to strings",
            "chapter":  "Chapter08",
            "source":   ['Chapter08/tuple_to_string/main.cpp'],
        }, {
            "title":    "Splitting tuples",
            "chapter":  "Chapter08",
            "source":   ['Chapter08/splitting_tuple/main.cpp'],
        },



        {
            "title":    'Comparing strings in an ultra-fast manner',
            "chapter":  "Chapter09",
            "source":   ['Chapter09/hash/main.cpp'],
        }, {
            "title":    'Using an unordered set and map',
            "chapter":  "Chapter09",
            "source":   ['Chapter09/unordered/main.cpp'],
        }, {
            "title":    'Making a map, where value is also a key',
            "chapter":  "Chapter09",
            "source":   ['Chapter09/bimap/main.cpp'],
        }, {
            "title":    'Using multi-index containers',
            "chapter":  "Chapter09",
            "source":   ['Chapter09/multiindex/main.cpp'],
        }, {
            "title":    'Getting the benefits of single-linked list and memory pool',
            "chapter":  "Chapter09",
            "source":   ['Chapter09/slist_and_pool/main.cpp'],
            "compile":  "-lboost_system",
        }, {
            "title":    'Using flat associative containers',
            "chapter":  "Chapter09",
            "source":   ['Chapter09/flat/main.cpp'],
        },



        {
            "title":    'Detecting int128 support',
            "chapter":  "Chapter10",
            "source":   ['Chapter10/int128/main.cpp'],
        }, {
            "title":    'Detecting RTTI support',
            "chapter":  "Chapter10",
            "source":   ['Chapter10/no_rtti/main.cpp'],
        }, {
            "title":    'Speeding up compilation using C++11 extern templates',
            "chapter":  "Chapter10",
            "source":   ['Chapter10/extern_template/main.cpp'],
            "compile":  "-std=c++11",
        }, {
            "title":    'Writing metafunctions using simpler methods',
            "chapter":  "Chapter10",
            "source":   ['Chapter10/constexpr_c++11/main.cpp'],
            "compile":  "-std=c++11",
        }, {
            "title":    'Reducing code size and increasing performance of user-defined types (UDTs) in C++11',
            "chapter":  "Chapter10",
            "source":   ['Chapter10/noexcept_c++11/main.cpp'],
            "compile":  "-std=c++11",
        }, {
            "title":    'The portable way to export and import functions and classes',
            "chapter":  "Chapter10",
            "source":   ['Chapter10/export_import/main.cpp', 'Chapter10/my_library/my_library.cpp', 'Chapter10/my_library/my_library.hpp'],
        }, {
            "title":    'Detecting the Boost version and getting latest features',
            "chapter":  "Chapter10",
            "source":   ['Chapter10/version/main.cpp'],
        },



        {
            "title":    'Listing files in a directory',
            "chapter":  "Chapter11",
            "source":   ['Chapter11/listing_files/main.cpp'],
            "compile":  "-lboost_system -lboost_filesystem",
        }, {
            "title":    'Erasing and creating files and directories',
            "chapter":  "Chapter11",
            "source":   ['Chapter11/erasing_files/main.cpp'],
            "compile":  "-lboost_system -lboost_filesystem",
        }, {
            "title":    'Passing data quickly from one process to another',
            "chapter":  "Chapter11",
            "source":   ['Chapter11/interprocess_basics/main.cpp'],
            "compile":  "-lrt",
        }, {
            "title":    'Syncing interprocess communications',
            "chapter":  "Chapter11",
            "source":   ['Chapter11/interprocess_queue/main.cpp'],
            "compile":  "-lrt",
        }, {
            "title":    'Using pointers in shared memory',
            "chapter":  "Chapter11",
            "source":   ['Chapter11/interprocess_pointers/main.cpp'],
            "compile":  "-lrt",
        }, {
            "title":    'The fastest way to read files',
            "chapter":  "Chapter11",
            "source":   ['Chapter11/reading_files/main.cpp'],
        }, {
            "title":    'Coroutines – saving the state and postponing the execution',
            "chapter":  "Chapter11",
            "source":   ['Chapter11/coroutines/main.cpp'],
            "compile":  "-lboost_coroutine -lboost_thread -lboost_system",
        },



        {
            "title":    'Working with graphs',
            "chapter":  "Chapter12",
            "source":   ['Chapter12/graph/main.cpp'],
        }, {
            "title":    'Visualizing graphs',
            "chapter":  "Chapter12",
            "source":   ['Chapter12/graph_vis/main.cpp'],
        }, {
            "title":    'Using a true random number generator',
            "chapter":  "Chapter12",
            "source":   ['Chapter12/random/main.cpp'],
            "compile":  "-lboost_random -lboost_system",
        }, {
            "title":    'Using portable math functions',
            "chapter":  "Chapter12",
            "source":   ['Chapter12/math/main.cpp'],
        }, {
            "title":    'Writing test cases',
            "chapter":  "Chapter12",
            "source":   ['Chapter12/testing/main.cpp'],
            "compile":  "-static -lboost_unit_test_framework -lboost_system",
        }, {
            "title":    'Combining multiple test cases in one test module',
            "chapter":  "Chapter12",
            "source":   ['Chapter12/testing_advanced/main.cpp', 'Chapter12/testing_advanced/developer1.cpp', 'Chapter12/testing_advanced/developer2.cpp', 'Chapter12/testing_advanced/foo.cpp', 'Chapter12/testing_advanced/foo.hpp'],
            "compile":  "-static -lboost_unit_test_framework -lboost_system",
        }, {
            "title":    'Manipulating images',
            "chapter":  "Chapter12",
            "source":   ['Chapter12/gil/main.cpp', 'Chapter12/testing_advanced/developer1.cpp'],
            "compile":  "-lpng",
        },

    ];

    var index = 0;
    var code;
    var command_line;
    var output;
    var recipe_title;
    var compile;

    function getUrlParameter(sParam) {
        var sPageURL = decodeURIComponent(window.location.search.substring(1)),
            sURLVariables = sPageURL.split('&'),
            sParameterName,
            i;

        for (i = 0; i < sURLVariables.length; i++) {
            sParameterName = sURLVariables[i].split('=');

            if (sParameterName[0] === sParam) {
                return sParameterName[1] === undefined ? true : sParameterName[1];
            }
        }
    };

    function download_impl_base(ind) {
        index = ind;
        $.get("https://raw.githubusercontent.com/apolukhin/Boost-Cookbook-4880OS/master/" + content[index]["source"][0], function(data) {
            code.text(data);
            command_line.val(content[index]['run']);
            output.text('');
            recipe_title.text("Recipe: " + content[index]["title"]);            
            if (!content[index]['compile']) {
                content[index]['compile'] = "";
            }
            compile.val("g++ -Wall main.cpp " + content[index]['compile'] + " -o main_prog");
            hljs.highlightBlock(code[0]);
        })
    };
    function download_impl(ind) {
        download_impl_base(ind);
        window.location="#online_example";
    };

    function process_remote_impl(cmd) {
        output.text('');
        var to_compile = {
            "src": code.text(),
            "cmd": cmd,
        };

        output.text("Executing... Please wait.");

        $.ajax({
          url: "http://coliru.stacked-crooked.com/compile",
          type: "POST",
          data: JSON.stringify(to_compile),
          contentType:"text/plain; charset=utf-8",
          dataType: "text"
        }).done(function(data) {
            output.text(data);
            hljs.highlightBlock(output[0]);
        }).fail(function(data) {
            output.text("Server error: " + data);
        });
    };

    function compile_impl() {
        process_remote_impl(
            compile.val() + " && echo 'Compilation: SUCCESS' "
        );
    };

    function run_impl() {
        if (!command_line.val()) {
            command_line.val("");
        }
        process_remote_impl(
            compile.val()
            + " && echo 'Compilation: SUCCESS\n\nProgram output:\n'  && ./main_prog " + command_line.val() + " && echo '\n\nRun: SUCCESS'"
        );
    };

    function init_impl(code_block, command_line_block, output_block, recipe_title_block, compile_block) {
        code = code_block;
        command_line = command_line_block;
        output = output_block;
        recipe_title = recipe_title_block;
        compile = compile_block;

        download_impl_base(0);
        chapter_show_base('01');
    };

    return {
        download: download_impl,
        compile: compile_impl,
        run: run_impl,
        init: init_impl,
    };

})();

