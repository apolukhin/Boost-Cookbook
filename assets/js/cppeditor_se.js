var editor = (function() {
	var content = {
		"Chapter01": [
			{
				"title":	"Getting configuration options",
				"source":   ['Chapter01/01_A_program_options_base/main.cpp', 'Chapter01/01_B_program_options_short/main.cpp'],
				"compile":  "-lboost_program_options",
				"run":	  "--apples=10 --oranges=5",
			}, {
				"title":	"Storing any value in a container/variable",
				"source":   ['Chapter01/02_any/main.cpp'],
			}, {
				"title":	"Storing multiple chosen types in a variable/container",
				"source":   ['Chapter01/03_variant/main.cpp'],
			}, {
				"title":	"Using a safer way to work with a container that stores multiple chosen types",
				"source":   ['Chapter01/04_A_any_db_example/main.cpp', 'Chapter01/04_B_variant_db_example/main.cpp'],
			}, {
				"title":	"Returning a value or flag where there is no value",
				"source":   ['Chapter01/05_optional/main.cpp'],
			}, {
				"title":	"Returning an array from a function",
				"source":   ['Chapter01/06_array/main.cpp'],
			}, {
				"title":	"Combining multiple values into one",
				"source":   ['Chapter01/07_tuple/main.cpp'],
			}, {
				"title":	"Reordering the parameters of function",
				"source":   ['Chapter01/08_bind/main.cpp'],
			}, {
				"title":	"Binding a value as a function parameter",
				"source":   ['Chapter01/09_type_index/main.cpp'],
			}, {
				"title":	"Using the C++11 move emulation",
				"source":   ['Chapter01/10_move/main.cpp'],
			}, {
				"title":	"Making a noncopyable class",
				"source":   ['Chapter01/11_noncopyable/main.cpp'],
			}, {
				"title":	"Making a noncopyable but movable class",
				"source":   ['Chapter01/12_noncopyable_movable/main.cpp'],
			},
		],


		"Chapter02": [
			{
				"title":	"Managing pointers to classes that do not leave scope",
				"source":   ['Chapter02/01_scoped_ptr/main.cpp'],
			}, {
				"title":	"Reference counting of pointers to classes used across methods",
				"source":   ['Chapter02/02_shared_ptr/main.cpp'],
				"compile":  "-lboost_thread -lboost_system",
			}, {
				"title":	"Managing pointers to arrays that do not leave scope",
				"source":   ['Chapter02/03_scoped_array/main.cpp'],
			}, {
				"title":	"Reference counting pointers to arrays used across methods",
				"source":   ['Chapter02/04_shared_array/main.cpp'],
				"compile":  "-lboost_thread -lboost_system",
			}, {
				"title":	"Storing any functional objects in a variable",
				"source":   ['Chapter02/05_function_fobject/main.cpp', 'Chapter02/function_fpointer/main.cpp'],
			}, {
				"title":	"Passing a function pointer in a variable",
				"source":   ['Chapter02/06_function_fpointer/main.cpp'],
				"compile":  "-std=c++11",
			}, {
				"title":	"Passing C++11 lambda functions in a variable",
				"source":   ['Chapter02/07_function_lambda_c++11/main.cpp'],
				"compile":  "-std=c++11",
			}, {
				"title":	"Containers of pointers",
				"source":   ['Chapter02/08_ptr_container_c++11/main.cpp'],
				"compile":  "-std=c++11",
			}, {
				"title":	"Doing something at scope exit",
				"source":   ['Chapter02/09_scope_exit/main.cpp'],
			}, {
				"title":	"Initializing the base class by a member of the derived class",
				"source":   ['Chapter02/10_base_from_member/main.cpp'],
			},
		],

		"Chapter03": [
			{
				"title":	"Converting strings to numbers",
				"source":   ['Chapter03/01_lexical_to_number/main.cpp'],
			}, {
				"title":	"Converting numbers to strings",
				"source":   ['Chapter03/02_lexical_to_string/main.cpp'],
			}, {
				"title":	"Converting numbers to numbers",
				"source":   ['Chapter03/03_numeric_cast/main.cpp'],
			}, {
				"title":	"Converting user-defined types to/from strings",
				"source":   ['Chapter03/04_lexical_user_defined/main.cpp'],
			}, {
				"title":	"Casting polymorphic objects",
				"source":   ['Chapter03/05_polymorphic_cast/main.cpp'],
			}, {
				"title":	"Parsing simple input",
				"source":   ['Chapter03/06_spirit/main.cpp'],
			}, {
				"title":	"Parsing input",
				"source":   ['Chapter03/07_spirit_rules/main.cpp'],
				"issues":   "compile",
			},
		],

		"Chapter04": [
			{
				"title":	"Checking sizes at compile time",
				"source":   ['Chapter04/static_assert/main.cpp'],
			}, {
				"title":	"Enabling the usage of templated functions for integral types",
				"source":   ['Chapter04/enable_if_c/main.cpp'],
			}, {
				"title":	"Disabling templated functions' usage for real types",
				"source":   ['Chapter04/disable_if_c/main.cpp'],
			}, {
				"title":	"Creating a type from number",
				"source":   ['Chapter04/mpl_int_/main.cpp'],
			}, {
				"title":	"Implementing a type trait",
				"source":   ['Chapter04/is_stdvector/main.cpp'],
			}, {
				"title":	"Selecting an optimal operator for a template parameter",
				"source":   ['Chapter04/conditional/main.cpp'],
			}, {
				"title":	"Getting a type of expression in C++03",
				"source":   ['Chapter04/typeof/main.cpp'],
			},
		],



		"Chapter05": [
			{
				"title":	"Creating an execution thread",
				"source":   ['Chapter05/thread/main.cpp'],
				"compile":  "-lboost_thread -lboost_system",
				"issues":   "runtime",
			}, {
				"title":	"Syncing access to a common resource",
				"source":   ['Chapter05/mutex/main.cpp'],
				"compile":  "-lboost_thread -lboost_system",
			}, {
				"title":	"Fast access to common resource using atomics",
				"source":   ['Chapter05/atomics/main.cpp'],
				"compile":  "-lboost_thread -lboost_system",
			}, {
				"title":	"Creating a work_queue class",
				"source":   ['Chapter05/work_queue/main.cpp'],
				"compile":  "-lboost_thread -lboost_system",
			}, {
				"title":	"Multiple-readers-single-writer lock",
				"source":   ['Chapter05/shared_lock/main.cpp'],
				"compile":  "-lboost_thread -lboost_system",
			}, {
				"title":	"Creating variables that are unique per thread",
				"source":   ['Chapter05/thread_specific_ptr/main.cpp'],
				"compile":  "-lboost_thread -lboost_system",
			}, {
				"title":	"Interrupting a thread",
				"source":   ['Chapter05/interruptions/main.cpp'],
				"compile":  "-lboost_thread -lboost_system",
			}, {
				"title":	"Manipulating a group of threads",
				"source":   ['Chapter05/thread_group/main.cpp'],
				"compile":  "-lboost_thread -lboost_system",
			},
		],


		"Chapter06": [
			{
				"title":	"Registering a task for processing an arbitrary datatype",
				"source":   ['Chapter06/tasks_processor_base/main.cpp', 'Chapter06/tasks_processor_base/tasks_processor_base.hpp'],
				"compile":  "-lboost_thread -lboost_system",
				"issues":   "compile",
			}, {
				"title":	"Making timers and processing timer events as tasks",
				"source":   ['Chapter06/tasks_processor_timers/main.cpp', 'Chapter06/tasks_processor_timers/tasks_processor_timers.hpp'],
				"compile":  "-lboost_thread -lboost_system",
				"issues":   "compile",
			}, {
				"title":	"Network communication as a task",
				"source":   ['Chapter06/tasks_processor_network/main.cpp', 'Chapter06/tasks_processor_network/tasks_processor_network.hpp'],
				"compile":  "-lboost_thread -lboost_system",
				"issues":   "compile",
			}, {
				"title":	"Accepting incoming connections",
				"source":   ['Chapter06/tasks_processor_network/main.cpp', 'Chapter06/tasks_processor_network/tasks_processor_network.hpp'],
				"compile":  "-lboost_thread -lboost_system",
				"issues":   "compile",
			}, {
				"title":	"Executing different tasks in parallel",
				"source":   ['Chapter06/tasks_processor_multithread/main.cpp', 'Chapter06/tasks_processor_multithread/tasks_processor_multithread.hpp'],
				"compile":  "-lboost_thread -lboost_system",
				"issues":   "compile",
			}, {
				"title":	"Conveyor tasks processing",
				"source":   ['Chapter06/conveyor/main.cpp'],
				"compile":  "-lboost_thread -lboost_system",
			}, {
				"title":	"Making a nonblocking barrier",
				"source":   ['Chapter06/nonblocking_barrier/main.cpp'],
				"compile":  "-lboost_thread -lboost_system",
				"issues":   "compile",
			}, {
				"title":	"Storing an exception and making a task from it",
				"source":   ['Chapter06/exception_ptr/main.cpp'],
				"compile":  "-lboost_thread -lboost_system",
				"issues":   "compile",
			}, {
				"title":	"Getting and processing system signals as tasks",
				"source":   ['Chapter06/tasks_processor_signals/main.cpp', 'Chapter06/tasks_processor_signals/tasks_processor_signals.hpp'],
				"compile":  "-lboost_thread -lboost_system",
				"issues":   "compile",
			}, 
		],


		"Chapter07": [
			{
				"title":	"Changing cases and case-insensitive comparison",
				"source":   ['Chapter07/case_conv/main.cpp'],
			}, {
				"title":	"Matching strings using regular expressions",
				"source":   ['Chapter07/regex_match/main.cpp'],
				"compile":  "-lboost_regex",
				"issues":   "runtime",
			}, {
				"title":	"Searching and replacing strings using regular expressions",
				"source":   ['Chapter07/regex_replace/main.cpp'],
				"compile":  "-lboost_regex",
				"issues":   "runtime",
			}, {
				"title":	"Formatting strings using safe printf-like functions",
				"source":   ['Chapter07/format/main.cpp'],
			}, {
				"title":	"Replacing and erasing strings",
				"source":   ['Chapter07/string_algo/main.cpp'],
			}, {
				"title":	"Representing a string with two iterators",
				"source":   ['Chapter07/iterator_range/main.cpp'],
			}, {
				"title":	"Using a reference to string type",
				"source":   ['Chapter07/string_ref/main.cpp'],
			},
		],


		"Chapter08": [
			{
				"title":	'Using type "vector of types"',
				"source":   ['Chapter08/vector_of_types/main.cpp'],
			}, {
				"title":	'Manipulating a vector of types',
				"source":   ['Chapter08/manipulating_vector_of_types/main.cpp'],
			}, {
				"title":	"Getting a function's result type at compile time",
				"source":   ['Chapter08/result_of_c++11/main.cpp'],
				"compile":  "-std=c++11",
			}, {
				"title":	"Making a higher-order metafunction",
				"source":   ['Chapter08/higher_order_metafunctions/main.cpp'],
			}, {
				"title":	"Evaluating metafunctions lazily",
				"source":   ['Chapter08/lazy/main.cpp'],
			}, {
				"title":	"Converting all the tuple elements to strings",
				"source":   ['Chapter08/tuple_to_string/main.cpp'],
			}, {
				"title":	"Splitting tuples",
				"source":   ['Chapter08/splitting_tuple/main.cpp'],
			},
		],



		"Chapter09": [
			{
				"title":	'Comparing strings in an ultra-fast manner',
				"source":   ['Chapter09/hash/main.cpp'],
			}, {
				"title":	'Using an unordered set and map',
				"source":   ['Chapter09/unordered/main.cpp'],
			}, {
				"title":	'Making a map, where value is also a key',
				"source":   ['Chapter09/bimap/main.cpp'],
			}, {
				"title":	'Using multi-index containers',
				"source":   ['Chapter09/multiindex/main.cpp'],
			}, {
				"title":	'Getting the benefits of single-linked list and memory pool',
				"source":   ['Chapter09/slist_and_pool/main.cpp'],
				"compile":  "-lboost_system",
			}, {
				"title":	'Using flat associative containers',
				"source":   ['Chapter09/flat/main.cpp'],
			},
		],



		"Chapter10": [
			{
				"title":	'Detecting int128 support',
				"source":   ['Chapter10/int128/main.cpp'],
			}, {
				"title":	'Detecting RTTI support',
				"source":   ['Chapter10/no_rtti/main.cpp'],
			}, {
				"title":	'Speeding up compilation using C++11 extern templates',
				"source":   ['Chapter10/extern_template/main.cpp', 'Chapter10/extern_template/header.hpp'],
				"compile":  "-std=c++11",
				"issues":   "compile",
			}, {
				"title":	'Writing metafunctions using simpler methods',
				"source":   ['Chapter10/constexpr_c++11/main.cpp'],
				"compile":  "-std=c++11",
			}, {
				"title":	'Reducing code size and increasing performance of user-defined types (UDTs) in C++11',
				"source":   ['Chapter10/noexcept_c++11/main.cpp'],
				"compile":  "-std=c++11",
			}, {
				"title":	'The portable way to export and import functions and classes',
				"source":   ['Chapter10/export_import/main.cpp', 'Chapter10/my_library/my_library.cpp', 'Chapter10/my_library/my_library.hpp'],
				"issues":   "compile",
			}, {
				"title":	'Detecting the Boost version and getting latest features',
				"source":   ['Chapter10/version/main.cpp'],
			},
		],



		"Chapter11": [
			{
				"title":	'Listing files in a directory',
				"source":   ['Chapter11/listing_files/main.cpp'],
				"compile":  "-lboost_system -lboost_filesystem",
			}, {
				"title":	'Erasing and creating files and directories',
				"source":   ['Chapter11/erasing_files/main.cpp'],
				"compile":  "-lboost_system -lboost_filesystem",
			}, {
				"title":	'Passing data quickly from one process to another',
				"source":   ['Chapter11/interprocess_basics/main.cpp'],
				"compile":  "-lrt -pthread",
				"issues":   "runtime",
			}, {
				"title":	'Syncing interprocess communications',
				"source":   ['Chapter11/interprocess_queue/main.cpp'],
				"compile":  "-lrt -pthread",
				"issues":   "runtime",
			}, {
				"title":	'Using pointers in shared memory',
				"source":   ['Chapter11/interprocess_pointers/main.cpp'],
				"compile":  "-lrt -pthread",
				"issues":   "runtime",
			}, {
				"title":	'The fastest way to read files',
				"source":   ['Chapter11/reading_files/main.cpp'],
				"issues":   "runtime",
				"run":		"c",
			}, {
				"title":	'Coroutines – saving the state and postponing the execution',
				"source":   ['Chapter11/coroutines/main.cpp'],
				"compile":  "-lboost_coroutine -lboost_thread -lboost_system",
			},
		],


		"Chapter12": [
			{
				"title":	'Working with graphs',
				"source":   ['Chapter12/graph/main.cpp'],
			}, {
				"title":	'Visualizing graphs',
				"source":   ['Chapter12/graph_vis/main.cpp'],
				"issues":   "compile",
			}, {
				"title":	'Using a true random number generator',
				"source":   ['Chapter12/random/main.cpp'],
				"compile":  "-lboost_random -lboost_system",
			}, {
				"title":	'Using portable math functions',
				"source":   ['Chapter12/math/main.cpp'],
			}, {
				"title":	'Writing test cases',
				"source":   ['Chapter12/testing/main.cpp'],
				"compile":  "-static -lboost_unit_test_framework -lboost_system",
				"issues":   "compile",
			}, {
				"title":	'Combining multiple test cases in one test module',
				"source":   ['Chapter12/testing_advanced/main.cpp', 'Chapter12/testing_advanced/developer1.cpp', 'Chapter12/testing_advanced/developer2.cpp', 'Chapter12/testing_advanced/foo.cpp', 'Chapter12/testing_advanced/foo.hpp'],
				"compile":  "-static -lboost_unit_test_framework -lboost_system",
				"issues":   "compile",
			}, {
				"title":	'Manipulating images',
				"source":   ['Chapter12/gil/main.cpp', 'Chapter12/testing_advanced/developer1.cpp'],
				"compile":  "-lpng",
				"issues":   "compile",
			},
		],

	};


	var current_chapter = 0;
	var current_index = 0;
	var current_source = 0;
	var code;
	var command_line;
	var output;
	var recipe_title;
	var compile;

	function chapter_hide_all_impl() {
		$.each(content, function(i, val) { 
			$('#' + i).hide();
		});
	}

	function chapter_show_all_impl() {
		$.each(content, function(i, val) { 
			$('#' + i).show();
		});
	}

	function chapter_toggle_impl(chapter) {
		$('#Chapter' + chapter).toggle();
		var num = parseInt(chapter);
		num = num - 1;
		num = num + "";
		if (num.length < 2) {
			num = '0' + num;
		}
	}


	function download_impl_base(chapter, ind, source_num) {
		current_chapter = chapter;
		current_index = ind;

		c = content[chapter][ind];
		source_num = (typeof source_num !== 'undefined' ? source_num : 0);
		source_num = (source_num < c["source"].length ? source_num : 0);
		current_source = source_num;

		$(".code-intro").hide();
		$("#" + chapter + "-" + ind).show();
		$("#runtime-issues").hide();
		$("#compile-issues").hide();
		command_line.val(c['run']);
		code.setValue("// Downloading...");
		code.clearSelection();
		output.text('');
		if (c["issues"]) {
			$("#" + c["issues"] + "-issues").show();
		}
		recipe_title.html(
			'<span class="icon fa-bookmark-o"></span> ' + chapter + ". "
			+ c["title"]
			+ (c["source"].length > 1 ? " (part " + (source_num + 1) + ")": "")
		);

		if (!c['compile']) {
			c['compile'] = "";
		}
		compile.val("g++ -Wall main.cpp " + c['compile'] + " -o main_prog");

		$.get("https://raw.githubusercontent.com/apolukhin/Boost-Cookbook/second_edition/" + c["source"][source_num], function(data) {
			code.setValue(data);
			code.clearSelection();
		});
	};

	function set_local_url_impl() {
		window.location="#" + current_chapter + "-recipe" + current_index + "-part" + (current_source + 1);
	}

	function download_impl(chapter, ind, num) {
		download_impl_base(chapter, ind, num);
		$("#intros-link").click();
		window.setTimeout(set_local_url_impl, 1300); // Hack to keep URL's href correct
	};

	function next_impl() {
		if (content[current_chapter][current_index]["source"][current_source + 1]) {
			download_impl_base(current_chapter, current_index, current_source + 1);
		} else if (content[current_chapter][current_index + 1]) {
			download_impl_base(current_chapter, current_index + 1);
		} else {
			var chapters = ["Chapter01", "Chapter03", "Chapter02", "Chapter04", "Chapter05", "Chapter06", "Chapter07", "Chapter08", "Chapter09", "Chapter10", "Chapter11", "Chapter12", ];
			var next_ind = chapters.indexOf(current_chapter) + 1;
			if (next_ind >= chapters.length) {
				next_ind = 0;
			}
			download_impl_base(chapters[next_ind], 0);
		}
	}

	function prev_impl() {
		if (current_source > 0) {
			download_impl_base(current_chapter, current_index, current_source - 1);
		} else if (current_index > 0) {
			download_impl_base(current_chapter, current_index - 1, content[current_chapter][current_index - 1]["source"].length - 1);
		} else {
			var chapters = ["Chapter01", "Chapter03", "Chapter02", "Chapter04", "Chapter05", "Chapter06", "Chapter07", "Chapter08", "Chapter09", "Chapter10", "Chapter11", "Chapter12", ];
			var next_ind = chapters.indexOf(current_chapter) - 1;
			if (next_ind < 0) {
				next_ind = chapters.length - 1;
			}
			current_chapter = chapters[next_ind];
			current_index = content[current_chapter].length - 1;

			download_impl_base(current_chapter, current_index, content[current_chapter][current_index]["source"].length - 1);
		}
	}

	function process_remote_impl(cmd) {
		set_local_url_impl();
		output.text('');
		var to_compile = {
			"src": code.getValue(),
			"cmd": cmd,
		};

		output.text("Executing... Please wait.");

        if (location.protocol === 'https:') {
            // page is secure, c
            location.href = 'http:' + window.location.href.substring(window.location.protocol.length);
        }

		$.ajax({
		  url: "//coliru.stacked-crooked.com/compile",
		  type: "POST",
		  data: JSON.stringify(to_compile),
		  contentType:"text/plain; charset=utf-8",
		  dataType: "text"
		}).done(function(data) {
			output.text(data);
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
			+ " && echo 'Compilation: SUCCESS. Program output:\n' && ./main_prog " + command_line.val() + " && echo \"\nExit code: $?\""
		);
	};

	function init_impl(code_block, command_line_block, output_block, recipe_title_block, compile_block) {
		code = code_block;
		command_line = command_line_block;
		output = output_block;
		recipe_title = recipe_title_block;
		compile = compile_block;

		code.setTheme("ace/theme/textmate");
		code.getSession().setMode("ace/mode/c_cpp");
		code.setShowPrintMargin(false);
		code.setOptions({
			maxLines: Infinity,
			fontSize: "12pt",
		});
		code.$blockScrolling = Infinity;

		var loc = window.location + '';
		var m = loc.match( /#(Chapter\d+)-recipe(\d+)-part(\d+)/i );
		if (m && m[0]) {
			download_impl(m[1], m[2], m[3] - 1);
		} else {
			download_impl_base("Chapter01", 0, 0);
		}

/*
		var d = "";
		$.each(["Chapter06"], function(ignore, chapter) {
			var i = 0;
			$.each(content[chapter], function(key, value){
				d = d + "<li><a href=\"javascript:editor.download('" + chapter + "', " + i + ")\">" + value["title"];
				if (value["source"].length > 1) {
					d = d + " (part 1</a>";
					$.each(value["source"].slice(1), function(index) {
						d = d + ", <a href=\"javascript:editor.download('" + chapter + "', " + i + ", " + (index + 1) + ")\">part " + (index + 2) + "</a>";
					});
					d = d + ")";
				}
				d = d + "</li>\n";
				++ i;
			});
		});
		alert(d);*/
	};

	return {
		download: download_impl,
		compile: compile_impl,
		run: run_impl,
		init: init_impl,
		next: next_impl,
		prev: prev_impl,
		chapter_toggle: chapter_toggle_impl,
		chapter_show_all: chapter_show_all_impl,
		chapter_hide_all: chapter_hide_all_impl,
		set_local_url: set_local_url_impl,
	};

})();

