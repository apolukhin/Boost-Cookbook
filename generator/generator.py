#!/usr/local/bin/python
# -*- coding: utf-8 -*-


from generator_data import data
import os
import re

content = {
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
			"source":   ['Chapter01/07_A_tuple/main.cpp', 'Chapter01/07_B_tuple_construction_order/main.cpp'],
		}, {
			"title":	"Reordering the parameters of function",
			"source":   ['Chapter01/08_bind/main.cpp'],
		}, {
			"title":	"Binding a value as a function parameter",
			"source":   ['Chapter01/09_type_index/main.cpp'],
		}, {
			"title":	"Using the C++11 move emulation",
			"source":   ['Chapter01/10_A_move/main.cpp'],
		}, {
			"title":	"Making a noncopyable class",
			"source":   ['Chapter01/11_noncopyable/main.cpp'],
		}, {
			"title":	"Making a noncopyable but movable class",
			"source":   ['Chapter01/12_A_noncopyable_movable/main.cpp'],
		}, {
			"title":	"Using C++14 and C++11 algorithms",
			"source":   ['Chapter01/13_algorithm/main.cpp'],
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
			"source":   ['Chapter02/05_function_fobject/main.cpp'],
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
			"title":	"Converting smart pointers",
			"source":   ['Chapter03/05_pointer_cast/main.cpp'],
		}, {
			"title":	"Casting polymorphic objects",
			"source":   ['Chapter03/06_polymorphic_cast/main.cpp'],
		}, {
			"title":	"Parsing simple input",
			"source":   ['Chapter03/07_spirit/main.cpp'],
		}, {
			"title":	"Parsing input",
			"source":   ['Chapter03/08_spirit_rules/main.cpp'],
			"issues":   "compile",
		},
	],

	"Chapter04": [
		{
			"title":	"Checking sizes at compile time",
			"source":   ['Chapter04/01_static_assert/main.cpp'],
		}, {
			"title":	"Enabling the usage of templated functions for integral types",
			"source":   ['Chapter04/02_enable_if_c/main.cpp'],
		}, {
			"title":	"Disabling templated functions' usage for real types",
			"source":   ['Chapter04/03_disable_if_c/main.cpp'],
		}, {
			"title":	"Creating a type from number",
			"source":   ['Chapter04/04_mpl_int_/main.cpp'],
		}, {
			"title":	"Implementing a type trait",
			"source":   ['Chapter04/05_is_stdvector/main.cpp'],
		}, {
			"title":	"Selecting an optimal operator for a template parameter",
			"source":   ['Chapter04/06_conditional/main.cpp'],
		}, {
			"title":	"Getting a type of expression in C++03",
			"source":   ['Chapter04/07_typeof/main.cpp'],
		},
	],


	"Chapter05": [
		{
			"title":	"Creating an execution thread",
			"source":   ['Chapter05/01_thread/main.cpp'],
			"compile":  "-lboost_thread -lboost_system",
			"issues":   "runtime",
		}, {
			"title":	"Syncing access to a common resource",
			"source":   ['Chapter05/02_mutex/main.cpp'],
			"compile":  "-lboost_thread -lboost_system",
		}, {
			"title":	"Fast access to common resource using atomics",
			"source":   ['Chapter05/03_atomics/main.cpp'],
			"compile":  "-lboost_thread -lboost_system",
		}, {
			"title":	"Creating a work_queue class",
			"source":   ['Chapter05/04_work_queue/main.cpp'],
			"compile":  "-lboost_thread -lboost_system",
		}, {
			"title":	"Multiple-readers-single-writer lock",
			"source":   ['Chapter05/05_shared_lock/main.cpp'],
			"compile":  "-lboost_thread -lboost_system",
		}, {
			"title":	"Creating variables that are unique per thread",
			"source":   ['Chapter05/06_thread_specific_ptr/main.cpp'],
			"compile":  "-lboost_thread -lboost_system",
		}, {
			"title":	"Interrupting a thread",
			"source":   ['Chapter05/07_interruptions/main.cpp'],
			"compile":  "-lboost_thread -lboost_system",
		}, {
			"title":	"Manipulating a group of threads",
			"source":   ['Chapter05/08_thread_group/main.cpp'],
			"compile":  "-lboost_thread -lboost_system",
		}, {
			"title":	"Initializing a shared variable safely",
			"source":   ['Chapter05/09_once/main.cpp'],
			"compile":  "-lboost_thread -lboost_system",
		}, {
			"title":	"Locking multiple mutexes",
			"source":   ['Chapter05/10_locks/main.cpp'],
			"compile":  "-lboost_thread -lboost_system",
		},
	],


	"Chapter06": [
		{
			"title":	"Registering a task for processing an arbitrary datatype",
			"source":   ['Chapter06/flat/01_tasks_processor_base/main.cpp'],
			"compile":  "-lboost_thread -lboost_system"
		}, {
			"title":	"Making timers and processing timer events as tasks",
			"source":   ['Chapter06/flat/02_tasks_processor_timers/main.cpp'],
			"compile":  "-lboost_thread -lboost_system -DBOOST_ASIO_DISABLE_HANDLER_TYPE_REQUIREMENTS=1",
		}, {
			"title":	"Network communication as a task",
			"source":   ['Chapter06/flat/04_tasks_processor_network_accept/main.cpp'],
			"compile":  "-lboost_thread -lboost_system -DBOOST_ASIO_DISABLE_HANDLER_TYPE_REQUIREMENTS=1",
		}, {
			"title":	"Accepting incoming connections",
			"source":   ['Chapter06/flat/04_tasks_processor_network_accept/main.cpp'],
			"compile":  "-lboost_thread -lboost_system -DBOOST_ASIO_DISABLE_HANDLER_TYPE_REQUIREMENTS=1",
		}, {
			"title":	"Executing different tasks in parallel",
			"source":   ['Chapter06/flat/05_tasks_processor_multithread/main.cpp'],
			"compile":  "-lboost_thread -lboost_system -DBOOST_ASIO_DISABLE_HANDLER_TYPE_REQUIREMENTS=1",
		}, {
			"title":	"Pipeline tasks processing",
			"source":   ['Chapter06/06_conveyor/main.cpp'],
			"compile":  "-lboost_thread -lboost_system -DBOOST_ASIO_DISABLE_HANDLER_TYPE_REQUIREMENTS=1",
		}, {
			"title":	"Making a nonblocking barrier",
			"source":   ['Chapter06/flat/07_nonblocking_barrier/main.cpp'],
			"compile":  "-lboost_thread -lboost_system -DBOOST_ASIO_DISABLE_HANDLER_TYPE_REQUIREMENTS=1",
		}, {
			"title":	"Storing an exception and making a task from it",
			"source":   ['Chapter06/flat/08_exception_ptr/main.cpp'],
			"compile":  "-lboost_thread -lboost_system -DBOOST_ASIO_DISABLE_HANDLER_TYPE_REQUIREMENTS=1",
		}, {
			"title":	"Getting and processing system signals as tasks",
			"source":   ['Chapter06/flat/09_tasks_processor_signals/main.cpp'],
			"compile":  "-lboost_thread -lboost_system -DBOOST_ASIO_DISABLE_HANDLER_TYPE_REQUIREMENTS=1",
		}, 
	],


	"Chapter07": [
		{
			"title":	"Changing cases and case-insensitive comparison",
			"source":   ['Chapter07/01_case_conv/main.cpp'],
		}, {
			"title":	"Matching strings using regular expressions",
			"source":   ['Chapter07/02_regex_match/main.cpp'],
			"compile":  "-lboost_regex",
			"issues":   "runtime",
		}, {
			"title":	"Searching and replacing strings using regular expressions",
			"source":   ['Chapter07/03_regex_replace/main.cpp'],
			"compile":  "-lboost_regex",
			"issues":   "runtime",
		}, {
			"title":	"Formatting strings using safe printf-like functions",
			"source":   ['Chapter07/04_format/main.cpp'],
		}, {
			"title":	"Replacing and erasing strings",
			"source":   ['Chapter07/05_string_algo/main.cpp'],
		}, {
			"title":	"Representing a string with two iterators",
			"source":   ['Chapter07/06_iterator_range/main.cpp'],
		}, {
			"title":	"Using a reference to string type",
			"source":   ['Chapter07/07_string_view/main.cpp'],
		},
	],


	"Chapter08": [
		{
			"title":	'Using type "vector of types"',
			"source":   ['Chapter08/01_vector_of_types/main.cpp'],
		}, {
			"title":	'Manipulating a vector of types',
			"source":   ['Chapter08/02_manipulating_vector_of_types/main.cpp'],
		}, {
			"title":	"Getting a function's result type at compile time",
			"source":   ['Chapter08/03_result_of_c++11/main.cpp'],
			"compile":  "-std=c++11",
		}, {
			"title":	"Making a higher-order metafunction",
			"source":   ['Chapter08/04_higher_order_metafunctions/main.cpp'],
		}, {
			"title":	"Evaluating metafunctions lazily",
			"source":   ['Chapter08/05_lazy/main.cpp'],
		}, {
			"title":	"Converting all the tuple elements to strings",
			"source":   ['Chapter08/06_tuple_to_string/main.cpp'],
		}, {
			"title":	"Splitting tuples",
			"source":   ['Chapter08/07_splitting_tuple/main.cpp'],
		}, {
			"title":	"Manipulating heterogeneous containers in C++14",
			"source":   ['Chapter08/08_splitting_tuple_hana/main.cpp'],
			"compile":  "-std=c++14",
		},
	],



	"Chapter09": [
		{
			"title":	'Storing a few elements in sequence container',
			"source":   ['Chapter09/01_small_vector/main.cpp'],
		}, {
			"title":	'Storing at most N elements in sequence container',
			"source":   ['Chapter09/02_static_vector/main.cpp'],
		}, {
			"title":	'Comparing strings in an ultra-fast manner',
			"source":   ['Chapter09/03_hash/main.cpp'],
		}, {
			"title":	'Using an unordered set and map',
			"source":   ['Chapter09/04_unordered/main.cpp'],
		}, {
			"title":	'Making a map, where value is also a key',
			"source":   ['Chapter09/05_bimap/main.cpp'],
		}, {
			"title":	'Using multi-index containers',
			"source":   ['Chapter09/06_multiindex/main.cpp'],
		}, {
			"title":	'Getting the benefits of single-linked list and memory pool',
			"source":   ['Chapter09/07_slist_and_pool/main.cpp'],
			"compile":  "-lboost_system",
		}, {
			"title":	'Using flat associative containers',
			"source":   ['Chapter09/08_flat/main.cpp'],
		},
	],



	"Chapter10": [
		{
			"title":	'Detecting OS and compiler',
			"source":   ['Chapter10/01_predef/main.cpp'],
		}, 
		{
			"title":	'Detecting int128 support',
			"source":   ['Chapter10/02_int128/main.cpp'],
		}, {
			"title":	'Detecting and bypassing disabled RTTI',
			"source":   ['Chapter10/03_no_rtti/main.cpp'],
		}, {
			"title":	'Writing metafunctions using simpler methods',
			"source":   ['Chapter10/04_constexpr_c++11/main.cpp'],
			"compile":  "-std=c++11",
		}, {
			"title":	'Reducing code size and increasing performance of user-defined types (UDTs) in C++11',
			"source":   ['Chapter10/05_noexcept_c++11/main.cpp'],
			"compile":  "-std=c++11",
		}, {
			"title":	'The portable way to export and import functions and classes',
			"source":   ['Chapter10/06_B_export_import/main.cpp', 'Chapter10/06_A_my_library/my_library.cpp', 'Chapter10/06_A_my_library/my_library.hpp'],
			"issues":   "compile",
		}, {
			"title":	'Detecting the Boost version and getting latest features',
			"source":   ['Chapter10/07_version/main.cpp'],
		},
	],



	"Chapter11": [
		{
			"title":	'Listing files in a directory',
			"source":   ['Chapter11/01_listing_files/main.cpp'],
			"compile":  "-lboost_system -lboost_filesystem",
		}, {
			"title":	'Erasing and creating files and directories',
			"source":   ['Chapter11/02_erasing_files/main.cpp'],
			"compile":  "-lboost_system -lboost_filesystem",
		}, {
			"title":	'Writing and using plugins',
			"source":   ['Chapter11/03_C_dll_usage/main.cpp', 'Chapter11/03_A_plugin_hello/plugin_hello.cpp', 'Chapter11/03_B_plugin_do_not/plugin_do_not.cpp'],
			"compile":  "-ldl -lboost_filesystem",
			"issues":   "runtime",
		}, {
			"title":	'Getting backtrace – current call sequence',
			"source":   ['Chapter11/04_stacktrace/main.cpp'],
			"compile":  "-ldl"
		}, {
			"title":	'Passing data quickly from one process to another',
			"source":   ['Chapter11/05_interprocess_basics/main.cpp'],
			"compile":  "-lrt -pthread",
			"issues":   "runtime",
		}, {
			"title":	'Syncing interprocess communications',
			"source":   ['Chapter11/06_interprocess_queue/main.cpp'],
			"compile":  "-lrt -pthread",
			"issues":   "runtime",
		}, {
			"title":	'Using pointers in shared memory',
			"source":   ['Chapter11/07_interprocess_pointers/main.cpp'],
			"compile":  "-lrt -pthread",
			"issues":   "runtime",
		}, {
			"title":	'The fastest way to read files',
			"source":   ['Chapter11/08_reading_files/main.cpp'],
			"issues":   "runtime",
			"run":		"c",
		}, {
			"title":	'Coroutines – saving the state and postponing the execution',
			"source":   ['Chapter11/09_coroutines/main.cpp'],
			"compile":  "-lboost_thread -lboost_system -lboost_context",
		},
	],


	"Chapter12": [
		{
			"title":	'Working with graphs',
			"source":   ['Chapter12/01_graph/main.cpp'],
		}, {
			"title":	'Visualizing graphs',
			"source":   ['Chapter12/02_graph_vis/main.cpp'],
			"issues":   "compile",
		}, {
			"title":	'Using a true random number generator',
			"source":   ['Chapter12/03_random/main.cpp'],
			"compile":  "-lboost_random -lboost_system",
		}, {
			"title":	'Using portable math functions',
			"source":   ['Chapter12/04_math/main.cpp'],
		}, {
			"title":	'Writing test cases',
			"source":   ['Chapter12/05_testing/main.cpp'],
			"compile":  "-DBOOST_TEST_DYN_LINK -lboost_unit_test_framework -lboost_system",
		}, {
			"title":	'Combining multiple test cases in one test module',
			"source":   ['Chapter12/06_testing_advanced/main.cpp', 'Chapter12/06_testing_advanced/developer1.cpp', 'Chapter12/06_testing_advanced/developer2.cpp', 'Chapter12/06_testing_advanced/foo.cpp', 'Chapter12/06_testing_advanced/foo.hpp'],
			"compile":  "-static -lboost_unit_test_framework -lboost_system",
			"issues":   "compile",
		}, {
			"title":	'Manipulating images',
			"source":   ['Chapter12/07_gil/main.cpp'],
			"compile":  "-lpng",
			"issues":   "compile",
		},
	],

};

'''
def next_impl():
	if (content[current_chapter][current_index]["source"][current_source + 1]) {
		download_impl_base(current_chapter, current_index, current_source + 1);
	} else if (content[current_chapter][current_index + 1]) {
		download_impl_base(current_chapter, current_index + 1);
	} else {
		var chapters = ["Chapter01", "Chapter02", "Chapter03", "Chapter04", "Chapter05", "Chapter06", "Chapter07", "Chapter08", "Chapter09", "Chapter10", "Chapter11", "Chapter12", ];
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
			var chapters = ["Chapter01", "Chapter02", "Chapter03", "Chapter04", "Chapter05", "Chapter06", "Chapter07", "Chapter08", "Chapter09", "Chapter10", "Chapter11", "Chapter12", ];
			var next_ind = chapters.indexOf(current_chapter) - 1;
			if (next_ind < 0) {
				next_ind = chapters.length - 1;
			}
			current_chapter = chapters[next_ind];
			current_index = content[current_chapter].length - 1;

			download_impl_base(current_chapter, current_index, content[current_chapter][current_index]["source"].length - 1);
		}
	}

'''

######################################################################################################################################################################################
######################################################################################################################################################################################
######################################################################################################################################################################################

template = ""
with open('generator_template.html', 'r') as f:
    template = f.read()

for key, value in data.iteritems():
    with open(os.path.join('../second_edition', key) + ".html", 'w') as f:
        m = re.match('Chapter(\d+)-(\d+)', key)
        f.write(
            template.replace('<!-- {python_intro_body} -->', value).replace('<!-- {python_prev_url} -->', '').replace('<!-- {python_next_url} -->', '')
        )




