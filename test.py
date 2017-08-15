import os
import sys
import signal
import subprocess
import argparse

from shutil import copyfile
from time import sleep

class tester:
    canonize_output = False

    outputs = {}
    expected = {

        'Chapter01/01_A_program_options_base_10_20': ('Fruits count: 30\n', '', 0),
        'Chapter01/01_A_program_options_base_20_30': ('Fruits count: 50\n', '', 0),
        'Chapter01/01_A_program_options_base_help': ('All options:\n  --apples arg          how many apples do you have\n  --oranges arg         how many oranges do you have\n  --help                produce help message\n\n', '', 1),
        'Chapter01/01_B_program_options_short_10_20': ("Error: can not read options configuration file 'apples_oranges.cfg'\nFruits count: 30\n", '', 0),
        'Chapter01/01_B_program_options_short_20_30': ("Error: can not read options configuration file 'apples_oranges.cfg'\nFruits count: 50\n", '', 0),
        'Chapter01/01_B_program_options_short_70': ("Error: can not read options configuration file 'apples_oranges.cfg'\nError: the option '--oranges' is required but missing\n", '', 2),
        'Chapter01/01_B_program_options_short_80_cfg': ('Fruits count: 100\n', '', 0),
        'Chapter01/01_B_program_options_short_cfg': ('Fruits count: 30\n', '', 0),
        'Chapter01/01_B_program_options_short_help': ('All options:\n  -o [ --oranges ] arg      oranges that you have\n  --name arg                your name\n  --help                    produce help message\n  -a [ --apples ] arg (=10) apples that you have\n\n', '', 1),
        'Chapter01/01_B_program_options_short_no_params': ("Error: can not read options configuration file 'apples_oranges.cfg'\nError: the option '--oranges' is required but missing\n", '', 2),
        'Chapter01/02_any': ('Wow! That is great!\n', '', 0),
        'Chapter01/03_variant': ('Wow! That is great!\n', '', 0),
        'Chapter01/04_A_any_db_example': ('Sum of arithmetic types in database row is: 20.1\n', '', 0),
        'Chapter01/04_B_variant_db_example': ('Sum of arithmetic types in database row is: 20.1\n', '', 0),
        'Chapter01/05_optional': ('...trying again\n...trying again\nDevice is locked\nSuccess!\n', '', 0),
        'Chapter01/07_B_tuple_construction_order': ('012', '', 0),
        'Chapter01/09_type_index': ('T is d\nx is i\nT is double\nx is int&&\n', '', 0),
        'Chapter01/12_A_noncopyable_movable': ('no C++11\n', '', 0),
        'Chapter01/12_B_noncopyable_movable_c++11': ('C++11\n', '', 0),
        'Chapter01/13_algorithm': ('48656C6C6F20776F7264\n48656C6C6F20776F7264\n', '', 0),
        'Chapter03/01_lexical_to_number': ('bad lexical cast: source type value could not be interpreted as target\n', '', 0),
        'Chapter02/01_scoped_ptr': ('str == scoped_ptr\nstr == unique_ptr\n', '', 0),
        'Chapter03/03_numeric_cast': ('#47 bad numeric conversion: negative overflow\n#58 bad numeric conversion: positive overflow\n\n\n\nNEG OVERFLOW in #47 bad numeric conversion: negative overflow\nPOS OVERFLOW in #59 bad numeric conversion: positive overflow\n\n\n\nIt works! Not in range!\n', '', 0),
        'Chapter04/01_static_assert': ('01', '', 0),
        'Chapter04/04_mpl_int_': (' 0 1 2 \x03 4 5\n', '', 0),
        'Chapter05/03_atomics': ('shared_i == 0\n', '', 0),
        'Chapter05/09_once': ('Print once 0\n', '', 0),
        'Chapter06/01_tasks_processor_base': ('', 'Exception: Just checking\nThread interrupted\n', 0),
        'Chapter06/02_tasks_processor_timers': ('', 'Exception: It works!\n', 0),
        'Chapter06/08_exception_ptr': ('Lexical cast exception detected.\n\nCan not handle such exceptions:\nmain.cpp(48): Throw in function void func_test2()\nDynamic exception type: boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<std::logic_error> >\nstd::exception::what: Some fatal logic error\n\n', '', 0),
        'Chapter06/09_tasks_processor_signals': ('Captured 1 SIGINT\nCaptured 2 SIGINT\nCaptured 3 SIGINT\n', '', 0),
        'Chapter07/02_regex_match': ('Available regex syntaxes:\n\t[0] Perl\n\t[1] Perl case insensitive\n\t[2] POSIX extended\n\t[3] POSIX extended case insensitive\n\t[4] POSIX basic\n\t[5] POSIX basic case insensitive\n\nChoose regex syntax: Input regex: String to match: MATCH\nString to match: MATCH\nString to match: DOES NOT MATCH\nString to match: \nInput regex: String to match: MATCH\nString to match: MATCH\nString to match: DOES NOT MATCH\nString to match: DOES NOT MATCH\nString to match: \nInput regex: ', '', 0),
        'Chapter07/02_regex_match_bad_num': ('Available regex syntaxes:\n\t[0] Perl\n\t[1] Perl case insensitive\n\t[2] POSIX extended\n\t[3] POSIX extended case insensitive\n\t[4] POSIX basic\n\t[5] POSIX basic case insensitive\n\nChoose regex syntax: Incorrect number of regex syntax. Exiting... \n', '', 1),
        'Chapter07/02_regex_match_bad_regex': ('Available regex syntaxes:\n\t[0] Perl\n\t[1] Perl case insensitive\n\t[2] POSIX extended\n\t[3] POSIX extended case insensitive\n\t[4] POSIX basic\n\t[5] POSIX basic case insensitive\n\nChoose regex syntax: Input regex: Incorrect regex pattern!\nInput regex: ', '', 0),
        'Chapter07/02_regex_match_extra': ('Available regex syntaxes:\n\t[0] Perl\n\t[1] Perl case insensitive\n\t[2] POSIX extended\n\t[3] POSIX extended case insensitive\n\t[4] POSIX basic\n\t[5] POSIX basic case insensitive\n\nChoose regex syntax: Input regex: String to match: MATCH\nString to match: DOES NOT MATCH\nString to match: \nInput regex: ', '', 0),
        'Chapter07/03_regex_replace': ('Available regex syntaxes:\n\t[0] Perl\n\t[1] Perl case insensitive\n\t[2] POSIX extended\n\t[3] POSIX extended case insensitive\n\t[4] POSIX basic\n\t[5] POSIX basic case insensitive\n\nChoose regex syntax: \nInput regex: String to match: DOES NOT MATCH\nString to match: MATCH: 4, 2, \nReplace pattern: RESULT: ###4-4-2-4-4###\nString to match: \n\nInput regex: ', '', 0),
        'Chapter07/03_regex_replace_bad_num': ('Available regex syntaxes:\n\t[0] Perl\n\t[1] Perl case insensitive\n\t[2] POSIX extended\n\t[3] POSIX extended case insensitive\n\t[4] POSIX basic\n\t[5] POSIX basic case insensitive\n\nChoose regex syntax: Incorrect number of regex syntax. Exiting... \n', '', 1),
        'Chapter07/03_regex_replace_bad_regex': ('Available regex syntaxes:\n\t[0] Perl\n\t[1] Perl case insensitive\n\t[2] POSIX extended\n\t[3] POSIX extended case insensitive\n\t[4] POSIX basic\n\t[5] POSIX basic case insensitive\n\nChoose regex syntax: \nInput regex: Incorrect regex pattern!\n\nInput regex: ', '', 0),
        'Chapter07/03_regex_replace_extra': ('Available regex syntaxes:\n\t[0] Perl\n\t[1] Perl case insensitive\n\t[2] POSIX extended\n\t[3] POSIX extended case insensitive\n\t[4] POSIX basic\n\t[5] POSIX basic case insensitive\n\nChoose regex syntax: \nInput regex: String to match: MATCH: q, w, e, \nReplace pattern: RESULT: ewq\nString to match: \n\nInput regex: ', '', 0),
        'Chapter07/04_format': ('Hello, dear Reader! Did you read the book for 100 % !\n100 == 100 && 100% != 100\n\nReader\n\nboost::too_few_args: format-string referred to more arguments than were passed\n', '', 0),
        'Chapter07/05_string_algo': ('\n erase_all_copy  :Hello hello dear Reader.\n erase_first_copy:Hello hello, dear Reader.\n erase_last_copy :Hello, hello dear Reader.\n ierase_all_copy :, , dear Reader.\n ierase_nth_copy :Hello, hello dear Reader.\n replace_all_copy  :Hello! hello! dear Reader.\n replace_first_copy  :Hello! hello, dear Reader.\n replace_head_copy  :Whaaaaaaa! hello, dear Reader.', '', 0),
        'Chapter07/06_iterator_range': ('Sentence #1 : \tThis is a long long character array\n35 characters.\nSentence has 6 whitespaces.\n\nSentence #2 : \tPlease split this character array to sentences\n46 characters.\nSentence has 6 whitespaces.\n\nSentence #3 : \tDo you know, that sentences are separated using period, exclamation mark and question mark\n90 characters.\nSentence has 13 whitespaces.\n\nSentence #4 : \t :-)\n4 characters.\nSentence has 1 whitespaces.\n\n', '', 0),
        'Chapter07/07_string_view': ('between brackets\nexpression\no_o\nO_O\n^_^\n', '', 0),
        'Chapter08/01_vector_of_types': ('N5boost3mpl6v_itemIN4mpl_6size_tILm32EEENS1_INS3_ILm1EEENS1_INS3_ILm4096EEENS1_INS3_ILm8EEENS1_INS3_ILm4EEENS0_7vector0INS2_2naEEELi0EEELi0EEELi0EEELi0EEELi0EEE', '', 0),
        'Chapter08/02_manipulating_vector_of_types': ('N4mpl_5long_ILl4EEE\n', '', 0),
        'Chapter08/06_tuple_to_string': ('Meow! 0_0\nMeow! 0_0\nMeow! Meow! \nMeow! Meow! Meow! Meow! Meow! Meow! Meow! Meow! Meow! Meow! \n', '', 0),
        'Chapter09/03_hash_h': ('HASH matched: 800000\n', '', 0),
        'Chapter09/03_hash_s': ('STD matched: 800000\n', '', 0),
        'Chapter09/03_hash_x': ('', '', 2),
        'Chapter09/05_bimap': ('Left:\nAnton Polukhin <=> 3\nAntony Polukhin <=> 3\nJohn Snow <=> 1\nVasya Pupkin <=> 2\n\nRight:\n1 <=> John Snow\n2 <=> Vasya Pupkin\n3 <=> Antony Polukhin\n3 <=> Anton Polukhin\n', '', 0),
        'Chapter09/06_multiindex': ('0:\nAnton Polukhin, 3, 182, 70\nAntony Polukhin, 3, 183, 70\nJohn Snow, 1, 185, 80\nVasya Pupkin, 2, 165, 60\n\n1:\nJohn Snow, 1, 185, 80\nVasya Pupkin, 2, 165, 60\nAnton Polukhin, 3, 182, 70\nAntony Polukhin, 3, 183, 70\n\n2:\nVasya Pupkin, 2, 165, 60\nAnton Polukhin, 3, 182, 70\nAntony Polukhin, 3, 183, 70\nJohn Snow, 1, 185, 80\n\n3:\nVasya Pupkin, 2, 165, 60\nAntony Polukhin, 3, 183, 70\nAnton Polukhin, 3, 182, 70\nJohn Snow, 1, 185, 80\n\n', '', 0),
        'Chapter09/07_slist_and_pool_l': ('std::list: ', '', 0),
        'Chapter09/07_slist_and_pool_s': ('slist_t:   ', '', 0),
        'Chapter09/07_slist_and_pool_x': ("Use 's' for testsing slist performance and 'l' for testsing std::list performance.", '', 0),
        'Chapter10/03_no_rtti': ('type_index type_id() [with T = double]', '', 0),
        'Chapter11/02_erasing_files': ('', 'Symlink created\n', 0),
        'Chapter11/02_erasing_files_second_run': ('', 'Failed to create a symlink\n', 0),
        'Chapter11/03_C_dll_usage_do_not': ("They are fast. Faster than you can believe. Don't turn your back, don't look away, and don't blink. Good luck, Sally Sparrow.", '', 0),
        'Chapter11/03_C_dll_usage_hello': ('Good to meet you, Sally Sparrow.', '', 0),
        'Chapter11/05_interprocess_basics': ('I have index 1. Press any key...\nI have index 2. Press any key...\nI have index 3. Press any key...\nI have index 4. Press any key...\nI have index 5. Press any key...\n', '', 0),
        'Chapter11/06_interprocess_queue': ('Filling data\nGettinging data\n', '', 0),
        'Chapter11/07_interprocess_pointers': ('Creating structure\nStructure found\n', '', 0),
        'Chapter11/08_reading_files_c_files': ('C:', '', 0),
        'Chapter11/08_reading_files_create_file': ('', '', 0),
        'Chapter11/08_reading_files_error': ('', '', 42),
        'Chapter11/08_reading_files_ifstream': ('ifstream:', '', 0),
        'Chapter11/08_reading_files_mmap': ('mapped_region:', '', 0),
        'Chapter11/09_coroutines': ('OK\n', '', 0),
        'Chapter12/01_graph': ('Boost\nC++ guru\n', '', 0),
        'Chapter12/02_graph_vis': ('digraph G {\n0 [label="C++"];\n1 [label="STL"];\n2 [label="Boost"];\n3 [label="C++ guru"];\n4 [label="C"];\n0->1 ;\n1->2 ;\n2->3 ;\n4->3 ;\n}\n', '', 0),
        'Chapter12/05_testing': ('Running 2 test cases...\n', '\n*** No errors detected\n', 0),
        'Chapter12/06_testing_advanced': ('Running 2 test cases...\n', '\n*** No errors detected\n', 0),


    }
    was_error = False

    ''' ****************************************** Main functions for testing ************************************* '''
    @staticmethod
    def safe_wait(task, timeout = 15.0):
        # Appveyor may hang on some test. This is a way to early abort
        delay = 0.5
        while task.poll() is None and timeout > 0:
             sleep(delay)
             timeout -= delay
        if timeout == 0:
            task.kill()
            print '!!! Test timeout !!!'
            sys.exit(-4)
        return task.communicate()

    @staticmethod
    def _test(command, test_name):
        proc = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        out1, out2 = tester.safe_wait(proc)
        tester.outputs[test_name] = (out1, out2, proc.returncode)
        tester._test_validate(test_name)

    @staticmethod
    def _print_test_output(test_name):
        out = tester.outputs[test_name]
        print '--- Stdout:\n{}\n--- Stderr:\n{}\n--- Ret code: {}\n'.format(out[0], out[1], out[2])

    @staticmethod
    def _test_validate(test_name):
        if tester.canonize_output:
            return

        if tester.outputs[test_name][0] == '' and tester.outputs[test_name][1] == '' and tester.outputs[test_name][2] == 0:
            return

        tester.outputs[test_name] = (
            tester.outputs[test_name][0].replace('\r', ''),
            tester.outputs[test_name][1].replace('\r', ''),
            tester.outputs[test_name][2],
        )

        if test_name not in tester.expected:
            print '"{}" must not produce output and finish with code 0. Info:'.format(test_name)
            tester._print_test_output(test_name)
            tester.was_error = True
            return

        if tester.outputs[test_name][2] != tester.expected[test_name][2]:
            print 'Return code in "{}" test is {}, {} expected. Info:'.format(test_name, tester.outputs[test_name][2], tester.expected[test_name][2])
            tester._print_test_output(test_name)
            tester.was_error = True

        if tester.outputs[test_name][0] != tester.expected[test_name][0]:
            print 'Output in "{}" test is {}, {} expected. Info:'.format(test_name, tester.outputs[test_name][0], tester.expected[test_name][0])
            tester._print_test_output(test_name)
            tester.was_error = True

    ''' ****************************************** Special testing cases ****************************************** '''
    @staticmethod
    def _test_program_options_base(test_name, path):
        command = [path, '--apples=10', '--oranges=20']
        tester._test(command, test_name + "_10_20")

        command = [path, '--apples=20', '--oranges=30']
        tester._test(command, test_name + "_20_30")

        command = [path, '--help']
        tester._test(command, test_name + "_help")

        command = [path, '--apples=70']
        # Test throws bad_any_cast as there's no '--oranges' parameter
        proc = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        out1, out2 = tester.safe_wait(proc)
        if proc.returncode == 0:
            print '"01_A_program_options_base_70" must finish with code != 0.'
            tester.was_error = True
            return

    @staticmethod
    def _test_program_options_short(test_name, path):
        command = [path, '--help']
        tester._test(command, test_name + "_help")

        command = [path]
        tester._test(command, test_name + "_no_params")

        command = [path, '-a', '10', '--oranges=20']
        tester._test(command, test_name + "_10_20")

        command = [path, '--apples=20', '--oranges=30']
        tester._test(command, test_name + "_20_30")

        command = [path, '--apples=70']
        tester._test(command, test_name + "_70")

        copyfile(
            os.path.join(test_name, "apples_oranges.cfg")
            , "./apples_oranges.cfg"
        )
        command = [path, '--apples=80']
        tester._test(command, test_name + "_80_cfg")

        command = [path]
        tester._test(command, test_name + "_cfg")
        os.remove("./apples_oranges.cfg")

    @staticmethod
    def _test_tasks_processor_signals(test_name, path):
        if os.name == 'nt':
            return # Signals and Windows are not pals!

        proc = subprocess.Popen(path, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        sleep(1)
        proc.send_signal(signal.SIGINT)
        sleep(0.5)
        proc.send_signal(signal.SIGINT)
        sleep(0.5)
        proc.send_signal(signal.SIGINT)

        out1, out2 = tester.safe_wait(proc)
        tester.outputs[test_name] = (out1, out2, proc.returncode)
        tester._test_validate(test_name)

    @staticmethod
    def _test_regex_bad(test_name, path):
        proc = subprocess.Popen(path, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        inp = "6\n"
        out1, out2 = proc.communicate(input=inp)

        tester.outputs[test_name + "_bad_num"] = (out1, out2, proc.returncode)
        tester._test_validate(test_name + "_bad_num")

        proc = subprocess.Popen(path, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        inp = "0\n(\\"
        out1, out2 = proc.communicate(input=inp)

        tester.outputs[test_name + "_bad_regex"] = (out1, out2, proc.returncode)
        tester._test_validate(test_name + "_bad_regex")


    @staticmethod
    def _test_regex_match(test_name, path):
        proc = subprocess.Popen(path, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

        out1, out2 = proc.communicate(
            input=b"0\n(\d{3}[#-]){2}\n123-123#\n312-321-\n21-123-\n\n\n\l{3,5}\nqwe\nqwert\nqwerty\nQWE\n\n\n"
        )
        tester.outputs[test_name] = (out1, out2, proc.returncode)
        tester._test_validate(test_name)

        for i in xrange(2, 6):
            proc = subprocess.Popen(path, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            inp = str(i) + b"\n...\nqwe\nqwerty"
            out1, out2 = proc.communicate(input=inp)

            tester.outputs[test_name + "_extra"] = (out1, out2, proc.returncode)
            tester._test_validate(test_name + "_extra")

        tester._test_regex_bad(test_name, path)

    @staticmethod
    def _test_regex_replace(test_name, path):
        proc = subprocess.Popen(path, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

        out1, out2 = proc.communicate(
            input=b"0\n(\d)(\d)\n\\1#\\2\n42\n###\\1-\\1-\\2-\\1-\\1###"
        )
        tester.outputs[test_name] = (out1, out2, proc.returncode)
        tester._test_validate(test_name)

        for i in xrange(6):
            proc = subprocess.Popen(path, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            inp = str(i)
            if i >= 4:
                inp += b"\n\\(.\\)\\(.\\)\\(.\\)\nqwe\n\\3\\2\\1"
            else:
                inp += b"\n(.)(.)(.)\nqwe\n\\3\\2\\1"

            out1, out2 = proc.communicate(input=inp)

            tester.outputs[test_name + "_extra"] = (out1, out2, proc.returncode)
            tester._test_validate(test_name + "_extra")

        tester._test_regex_bad(test_name, path)

    @staticmethod
    def _test_export_import(test_name, path):
        try:
            copyfile(
                "Chapter10/06_A_my_library/debug/06_A_my_library.dll",
                "./06_A_my_library.dll"
            )
        except:
            pass

        try:
            copyfile(
                "Chapter10/06_A_my_library/release/06_A_my_library.dll",
                "./06_A_my_library.dll"
            )
        except:
            pass

        tester._test(path, test_name)

    @staticmethod
    def _test_hash(test_name, path):
        tester._test(path, test_name)
        tester._test([path, 'h'], test_name + '_h')
        tester._test([path, 's'], test_name + '_s')
        tester._test([path, 'x'], test_name + '_x')

    @staticmethod
    def _test_slist_and_pool(test_name, path):
        tester._test(path, test_name)
        tester._test([path, 's'], test_name + '_s')
        tester._test([path, 'l'], test_name + '_l')
        tester._test([path, 'x'], test_name + '_x')

    @staticmethod
    def _test_erasing_files(test_name, path):
        tester._test(path, test_name)
        tester._test(path, test_name + '_second_run')

    @staticmethod
    def _test_plugins(test_name, path):
        plugins = []
        for folder, _, files in os.walk('Chapter11'):
            for f in files:
                if 'plugin' not in f:
                    continue

                plugin_path = os.path.join(folder, f)
                if plugin_path.endswith('.so') or plugin_path.endswith('.dll'):
                    plugins.append(plugin_path)

        for p in plugins:
            new_test_name = test_name
            if 'hello' in p:
                tester._test([path, p], test_name + '_hello')
            else:
                tester._test([path, p], test_name + '_do_not')

    @staticmethod
    def _test_interprocess_basic(test_name, path):
        procs = []
        for x in xrange(5):
            procs.append( subprocess.Popen(path, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE) )
            sleep(0.5) # Giving time for processes to start

        out1 = ""
        out2 = ""
        retcode = 0
        for p in procs:
            out1_tmp, out2_tmp = p.communicate(input='any_key')
            out1 += out1_tmp
            out2 += out2_tmp
            retcode += p.returncode

        tester.outputs[test_name] = (out1, out2, retcode)
        tester._test_validate(test_name)

    @staticmethod
    def _test_reading_files(test_name, path):
        tester._test([path, 'c'], test_name + '_create_file')
        tester._test([path, 'm'], test_name + '_mmap')
        tester._test([path, 'r'], test_name + '_ifstream')
        tester._test([path, 'a'], test_name + '_c_files')
        tester._test([path, 'e'], test_name + '_error')

    @staticmethod
    def _test_interprocess_run_two_concurrently(test_name, path):
        procs = []
        for x in xrange(2):
            procs.append( subprocess.Popen(path, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE) )
            sleep(0.5) # Giving time for processes to start

        out1 = ""
        out2 = ""
        retcode = 0
        for p in procs:
            out1_tmp, out2_tmp = tester.safe_wait(p)
            out1 += out1_tmp
            out2 += out2_tmp
            retcode += p.returncode

        tester.outputs[test_name] = (out1, out2, retcode)
        tester._test_validate(test_name)

    @staticmethod
    def _test_gil(test_name, path):
        tester._test(path, test_name)

    @staticmethod
    def _test_but_ignore_output_diff(test_name, path):
        proc = subprocess.Popen(path, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
        out1, out2 = tester.safe_wait(proc)
        if out1 == '' and out2 == '':
            print 'No output in "{}" test\n'.format(test_name)
            tester.was_error = True

        tester.outputs[test_name] = (out1, out2, proc.returncode)
        if tester.canonize_output:
            return

        if proc.returncode != 0:
            print 'Return code in "{}" test is {}, {} expected. Info:'.format(test_name, tester.outputs[test_name][2], tester.expected[test_name][2])
            tester._print_test_output(test_name)
            tester.was_error = True


    @staticmethod
    def _ignore(test_name, path):
        pass

    ''' ****************************************** Private functions ********************************************** '''
    @staticmethod
    def _test_recipe(path):
        special_cases = {
            "Chapter01/01_A_program_options_base": tester._test_program_options_base,
            "Chapter01/01_B_program_options_short": tester._test_program_options_short,
            "Chapter01/09_type_index": tester._test_but_ignore_output_diff,                     # Different demangled representation of a type
            "Chapter01/12_A_noncopyable_movable": tester._test_but_ignore_output_diff,          # Different C++11 support
            "Chapter05/02_mutex": tester._test_but_ignore_output_diff,                          # Intentionally has data race
            "Chapter06/08_exception_ptr": tester._test_but_ignore_output_diff,                  # Different demangled exception name
            "Chapter06/09_tasks_processor_signals": tester._test_tasks_processor_signals,
            "Chapter07/02_regex_match": tester._test_regex_match,
            "Chapter07/03_regex_replace": tester._test_regex_replace,
            'Chapter08/01_vector_of_types': tester._test_but_ignore_output_diff,                # Different manglings
            'Chapter08/02_manipulating_vector_of_types': tester._test_but_ignore_output_diff,   # Different manglings
            'Chapter09/03_hash': tester._test_hash,
            'Chapter09/04_unordered': tester._test_but_ignore_output_diff,
            'Chapter09/07_slist_and_pool': tester._test_slist_and_pool,
            "Chapter10/03_no_rtti": tester._test_but_ignore_output_diff,                        # Different demangled representation of a type
            "Chapter10/06_B_export_import": tester._test_export_import,
            "Chapter11/01_listing_files": tester._test_but_ignore_output_diff,
            "Chapter11/02_erasing_files": tester._test_erasing_files,
            "Chapter11/03_C_dll_usage": tester._test_plugins,
            "Chapter11/04_stacktrace": tester._test_but_ignore_output_diff,
            "Chapter11/05_interprocess_basics": tester._test_interprocess_basic,
            "Chapter11/06_interprocess_queue": tester._test_interprocess_run_two_concurrently,
            "Chapter11/07_interprocess_pointers": tester._test_interprocess_run_two_concurrently,
            "Chapter11/08_reading_files": tester._test_reading_files,
            "Chapter11/09_coroutines": tester._test_but_ignore_output_diff, # Sanitizers do not like coroutines and add some warnings
            "Chapter12/03_random": tester._test_but_ignore_output_diff,

            # TODO:
            "Chapter12/07_gil": tester._ignore, #tester._test_gil,
        }

        test_name = os.path.dirname(os.path.relpath(path)).replace('\\release', '').replace('\\debug', '').replace('\\', '/')
        print "* {}".format(test_name)
        test_name = test_name.replace('/flat', '').replace('\\flat', '')
        if test_name in special_cases:
            f = special_cases[test_name]
            f(test_name, path)
        else:
            tester._test(path, test_name)

    @staticmethod
    def _print_outputs():
        print "\n\nOutput"
        for o in sorted(tester.outputs):
            print "        '{}': {},".format(o, tester.outputs[o])

    @staticmethod
    def _print_outputs_short():
        print "\n\nOutput"
        for o in sorted(tester.outputs):
            if tester.outputs[o][0] != '' or tester.outputs[o][1] != '' or tester.outputs[o][2] != 0:
                print "        '{}': {},".format(o, tester.outputs[o])

    @staticmethod
    def _is_exe(path):
        return os.path.isfile(path) and os.access(path, os.X_OK) and (os.name != 'nt' or '.exe' in path) and '/.git/' not in path and '.sh' not in path and '.so' not in path

    ''' ****************************************** Public functions *********************************************** '''
    @staticmethod
    def run_tests(root_directory='.', verbose=False):
        print "Searching for executables..."
        executables = []
        for folder, _, files in os.walk(root_directory):
            for f in files:
                path = os.path.join(folder, f)
                if tester._is_exe(path):
                    executables.append(path)

        executables.sort()

        print "\nStarting tests..."
        for e in executables:
            tester._test_recipe(e)
        print "... tests finished"

        if tester.canonize_output:
            tester._print_outputs_short()
            sys.exit(-3)

        if verbose or tester.was_error:
            tester._print_outputs()

        if tester.was_error:
            print "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! FAILURE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
            sys.exit(-1)

        print "\n*** SUCESS ***"


if __name__ == "__main__":
    print "Initializing"
    parser = argparse.ArgumentParser(description='Process some integers.')
    parser.add_argument('--dir',  default='.', help='Directory (chapter) to run tests for')
    parser.add_argument('--build', '-b', action='store_true', help='Build the recipes for Linux platform')
    parser.add_argument('--verbose', '-v', action='store_true', help='Output all the results')
    args = parser.parse_args()

    if args.build:
        old_path = os.getcwd()
        os.chdir(args.dir)
        subprocess.check_call(['qmake', '.'])
        subprocess.check_call(['make', '-j4'])
        os.chdir(old_path)

    tester.run_tests(args.dir, args.verbose)

    if args.build:
        old_path = os.getcwd()
        os.chdir(args.dir)
        subprocess.check_call(['make', 'distclean'])
        os.chdir(old_path)

