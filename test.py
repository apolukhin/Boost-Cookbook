import os
import sys
import signal
import subprocess

from shutil import copyfile
from time import sleep

# ./bootstrap.sh
# ./b2 -j4 define=BOOST_THREAD_VERSION=4 address-model=64 architecture=x86 --with-program_options --with-filesystem --with-system --with-test --with-thread --with-chrono --with-regex --with-random --with-context --with-coroutine stage

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
        'Chapter01/01_B_program_options_short_help': ('All options:\n  -o [ --oranges ] arg      oranges that you have\n  --name arg                your name\n  -a [ --apples ] arg (=10) apples that you have\n  --help                    produce help message\n\n', '', 1),
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
        'Chapter02/01_scoped_ptr': ('str == scoped_ptr\nstr == unique_ptr\n', '', 0),
        'Chapter03/03_numeric_cast': ('#47 bad numeric conversion: negative overflow\n#58 bad numeric conversion: positive overflow\n\n\n\nNEG OVERFLOW in #47 bad numeric conversion: negative overflow\nPOS OVERFLOW in #59 bad numeric conversion: positive overflow\n\n\n\nIt works! Not in range!\n', '', 0),
        'Chapter04/01_static_assert': ('01', '', 0),
        'Chapter04/04_mpl_int_': (' 0 1 2 \x03 4 5\n', '', 0),
        'Chapter05/03_atomics': ('shared_i == 0\n', '', 0),
        'Chapter05/09_once': ('Print once 0\n', '', 0),
        'Chapter06/01_tasks_processor_base': ('', 'Exception: Just checking\nThread interrupted\n', 0),
        'Chapter06/02_tasks_processor_timers': ('', 'Exception: It works!\n', 0),
        'Chapter06/08_exception_ptr': ('Lexical cast exception detected\n\nCan not handle such exceptions:\nmain.cpp(48): Throw in function void func_test2()\nDynamic exception type: boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<std::logic_error> >\nstd::exception::what: Some fatal logic error\n\n', '', 0),
        'Chapter06/09_tasks_processor_signals': ('Captured 1 SIGINT\nCaptured 2 SIGINT\nCaptured 3 SIGINT\n', '', 0),
        'Chapter07/02_regex_match': ('Available regex syntaxes:\n\t[0] Perl\n\t[1] Perl case insensitive\n\t[2] POSIX extended\n\t[3] POSIX extended case insensitive\n\t[4] POSIX basic\n\t[5] POSIX basic case insensitive\nChoose regex syntax: Input regex: String to match: MATCH\nString to match: MATCH\nString to match: DOES NOT MATCH\nString to match: \nInput regex: String to match: MATCH\nString to match: MATCH\nString to match: DOES NOT MATCH\nString to match: DOES NOT MATCH\nString to match: \nInput regex: ', '', 0),
        'Chapter07/02_regex_match_extra': ('Available regex syntaxes:\n\t[0] Perl\n\t[1] Perl case insensitive\n\t[2] POSIX extended\n\t[3] POSIX extended case insensitive\n\t[4] POSIX basic\n\t[5] POSIX basic case insensitive\nChoose regex syntax: Input regex: String to match: MATCH\nString to match: DOES NOT MATCH\nString to match: \nInput regex: ', '', 0),
        'Chapter07/03_regex_replace': ('Available regex syntaxes:\n\t[0] Perl\n\t[1] Perl case insensitive\n\t[2] POSIX extended\n\t[3] POSIX extended case insensitive\n\t[4] POSIX basic\n\t[5] POSIX basic case insensitive\nChoose regex syntax: \nInput regex: String to match: DOES NOT MATCH\nString to match: MATCH: 4, 2, \nReplace pattern: RESULT: ###4-4-2-4-4###\nString to match: \n\nInput regex: ', '', 0),
        'Chapter07/03_regex_replace_extra': ('Available regex syntaxes:\n\t[0] Perl\n\t[1] Perl case insensitive\n\t[2] POSIX extended\n\t[3] POSIX extended case insensitive\n\t[4] POSIX basic\n\t[5] POSIX basic case insensitive\nChoose regex syntax: \nInput regex: String to match: MATCH: q, w, e, \nReplace pattern: RESULT: ewq\nString to match: \n\nInput regex: ', '', 0),
        'Chapter07/04_format': ('Hello, dear Reader! Did you read the book for 100 % !\n100 == 100 && 100% != 100\n\nReader\n\nboost::too_few_args: format-string referred to more arguments than were passed\n', '', 0),
        'Chapter07/05_string_algo': ('\n erase_all_copy   :Hello hello dear Reader.\n erase_first_copy :Hello hello, dear Reader.\n erase_last_copy  :Hello, hello dear Reader.\n ierase_all_copy  :, , dear Reader.\n ierase_nth_copy  :Hello, hello dear Reader.\n replace_all_copy  :Hello! hello! dear Reader.\n replace_first_copy  :Hello! hello, dear Reader.\n replace_head_copy  :Whaaaaaaa! hello, dear Reader.', '', 0),
        'Chapter07/06_iterator_range': ('Sentence #1 : \tThis is a long long character array\nSentence has 35 characters.\nSentence has 6 whitespaces.\n\nSentence #2 : \tPlease split this character array to sentences\nSentence has 46 characters.\nSentence has 6 whitespaces.\n\nSentence #3 : \tDo you know, that sentences are separated using period, exclamation mark and question mark\nSentence has 90 characters.\nSentence has 13 whitespaces.\n\nSentence #4 : \t :-)\nSentence has 4 characters.\nSentence has 1 whitespaces.\n\n', '', 0),
        'Chapter07/07_string_ref': ('between brackets\nexpression\no_o\nO_O\n^_^\n', '', 0),
        'Chapter08/01_vector_of_types': ('N5boost3mpl6v_itemIN4mpl_6size_tILm32EEENS1_INS3_ILm1EEENS1_INS3_ILm4096EEENS1_INS3_ILm8EEENS1_INS3_ILm4EEENS0_7vector0INS2_2naEEELi0EEELi0EEELi0EEELi0EEELi0EEE', '', 0),
        'Chapter08/02_manipulating_vector_of_types': ('N4mpl_5long_ILl4EEE\n', '', 0),
        'Chapter08/06_tuple_to_string': ('Meow! 0_0\nMeow! 0_0\nMeow! Meow! \nMeow! Meow! Meow! Meow! Meow! Meow! Meow! Meow! Meow! Meow! \n', '', 0),
        'Chapter09/bimap': ('Left:\nAnton Polukhin <=> 3\nAntony Polukhin <=> 3\nJohn Snow <=> 1\nVasya Pupkin <=> 2\n\nRight:\n1 <=> John Snow\n2 <=> Vasya Pupkin\n3 <=> Antony Polukhin\n3 <=> Anton Polukhin\n', '', 0),
        'Chapter09/multiindex': ('0:\nAnton Polukhin, 3, 182, 70\nAntony Polukhin, 3, 183, 70\nJohn Snow, 1, 185, 80\nVasya Pupkin, 2, 165, 60\n\n1:\nJohn Snow, 1, 185, 80\nVasya Pupkin, 2, 165, 60\nAnton Polukhin, 3, 182, 70\nAntony Polukhin, 3, 183, 70\n\n2:\nVasya Pupkin, 2, 165, 60\nAnton Polukhin, 3, 182, 70\nAntony Polukhin, 3, 183, 70\nJohn Snow, 1, 185, 80\n\n3:\nVasya Pupkin, 2, 165, 60\nAntony Polukhin, 3, 183, 70\nAnton Polukhin, 3, 182, 70\nJohn Snow, 1, 185, 80\n\n', '', 0),
        'Chapter09/unordered': ('boost::unordered_set<std::string> : B  A  CD  CZ  \nstd::set<std::string> : A  B  CD  CZ  \n', '', 0),
        'Chapter10/my_library': ('', '', -11),
        'Chapter10/no_rtti': ('type_index type_id() [with T = double]', '', 0),
        'Chapter11/erasing_files': ('', 'Failed to create a symlink\n', 0),
        'Chapter11/reading_files': ('', "reading_files: main.cpp:14: int main(int, char**): Assertion `argc >= 2' failed.\n", -6),
        'Chapter12/gil': ('', "terminate called after throwing an instance of 'std::ios_base::failure'\n  what():  file_mgr: failed to open file\n", -6),
        'Chapter12/graph': ('Boost\nC++ guru\n', '', 0),
        'Chapter12/graph_vis': ('digraph G {\n0 [label="C++"];\n1 [label="STL"];\n2 [label="Boost"];\n3 [label="C++ guru"];\n4 [label="C"];\n0->1 ;\n1->2 ;\n2->3 ;\n4->3 ;\n}\n', '', 0),
        'Chapter12/testing': ('Running 2 test cases...\n', '\n*** No errors detected\n', 0),
        'Chapter12/testing_advanced': ('Running 2 test cases...\n', '\n*** No errors detected\n', 0),


    }
    was_error = False

    ''' ****************************************** Main functions for testing ************************************* '''
    @staticmethod
    def _test(command, test_name):
        proc = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        out1, out2 = proc.communicate()
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
        out1, out2 = proc.communicate()
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
        proc = subprocess.Popen(path, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        sleep(1)
        proc.send_signal(signal.SIGINT)
        sleep(0.5)
        proc.send_signal(signal.SIGINT)
        sleep(0.5)
        proc.send_signal(signal.SIGINT)

        out1, out2 = proc.communicate()
        tester.outputs[test_name] = (out1, out2, proc.returncode)
        tester._test_validate(test_name)

    @staticmethod
    def _test_regex_match(test_name, path):
        proc = subprocess.Popen(path, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

        out1, out2 = proc.communicate(
            input=b"0\n(\d{3}[#-]){2}\n123-123#\n312-321-\n21-123-\n\n\n\l{3,5}\nqwe\nqwert\nqwerty\nQWE\n\n\n"
        )
        tester.outputs[test_name] = (out1, out2, proc.returncode)
        tester._test_validate(test_name)

        for i in xrange(2, 5):
            proc = subprocess.Popen(path, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            inp = str(i) + b"\n...\nqwe\nqwerty"
            out1, out2 = proc.communicate(input=inp)

            tester.outputs[test_name + "_extra"] = (out1, out2, proc.returncode)
            tester._test_validate(test_name + "_extra")

    @staticmethod
    def _test_regex_replace(test_name, path):
        proc = subprocess.Popen(path, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

        out1, out2 = proc.communicate(
            input=b"0\n(\d)(\d)\n\\1#\\2\n42\n###\\1-\\1-\\2-\\1-\\1###"
        )
        tester.outputs[test_name] = (out1, out2, proc.returncode)
        tester._test_validate(test_name)

        for i in xrange(4, 6):
            proc = subprocess.Popen(path, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            inp = str(i) + b"\n\\(.\\)\\(.\\)\\(.\\)\nqwe\n\\3\\2\\1"
            out1, out2 = proc.communicate(input=inp)

            tester.outputs[test_name + "_extra"] = (out1, out2, proc.returncode)
            tester._test_validate(test_name + "_extra")

    @staticmethod
    def _test_gil(test_name, path):
        command = [path, 'get-boost.png']
        tester._test(command, test_name)

    @staticmethod
    def _test_but_ignore_output_diff(test_name, path):
        proc = subprocess.Popen(path, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
        out1, out2 = proc.communicate()
        if out1 == '' and out2 == '':
            print 'No output in "{}" test\n'.format(test_name)
            tester.was_error = True

        tester.outputs[test_name] = ('', '', proc.returncode)
        tester._test_validate(test_name)


    @staticmethod
    def _ignore(test_name, path):
        pass

    ''' ****************************************** Private functions ********************************************** '''
    @staticmethod
    def _test_recipe(path):
        special_cases = {
            "Chapter01/01_A_program_options_base": tester._test_program_options_base,
            "Chapter01/01_B_program_options_short": tester._test_program_options_short,
            "Chapter06/09_tasks_processor_signals": tester._test_tasks_processor_signals,
            "Chapter07/02_regex_match": tester._test_regex_match,
            "Chapter07/03_regex_replace": tester._test_regex_replace,
            'Chapter08/01_vector_of_types': tester._test_but_ignore_output_diff, # Different manglings
            'Chapter08/02_manipulating_vector_of_types': tester._test_but_ignore_output_diff, # Different manglings
            "Chapter11/listing_files": tester._test_but_ignore_output_diff,
            "Chapter12/gil": tester._test_gil,
            "Chapter05/02_mutex": tester._test_but_ignore_output_diff,
            "Chapter11/coroutines": tester._test_but_ignore_output_diff, # Sanitizers do not like coroutines and add some warnings
            "Chapter12/random": tester._test_but_ignore_output_diff,

            "Chapter10/no_rtti": tester._ignore,
            "Chapter11/interprocess_basics": tester._ignore,
            "Chapter11/interprocess_pointers": tester._ignore,
            "Chapter11/interprocess_queue": tester._ignore,
            "Chapter11/interprocess_queue": tester._ignore,
        }

        test_name = os.path.dirname(os.path.relpath(path)).replace('\\release', '').replace('\\debug', '').replace('\\', '/')
        print "* {}".format(test_name)
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
        return os.path.isfile(path) and os.access(path, os.X_OK) and (os.name != 'nt' or '.exe' in path) and '/.git/' not in path and '.sh' not in path

    ''' ****************************************** Public functions *********************************************** '''
    @staticmethod
    def run_tests(root_directory='.'):
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

        if tester.was_error:
            tester._print_outputs()
            print "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! FAILURE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
            sys.exit(-1)

        print "\n*** SUCESS ***"


if __name__ == "__main__":
    import argparse
    parser = argparse.ArgumentParser(description='Process some integers.')
    parser.add_argument('--dir',  default='.', help='Directory (chapter) to run tests for')
    parser.add_argument('--build', '-b', action='store_true', help='Build the recipes for Linux platform')
    args = parser.parse_args()

    if args.build:
        old_path = os.getcwd()
        os.chdir(args.dir)
        subprocess.check_call(['qmake', '.'])
        subprocess.check_call(['make', '-j4'])
        os.chdir(old_path)

    tester.run_tests(args.dir)

    if args.build:
        old_path = os.getcwd()
        os.chdir(args.dir)
        subprocess.check_call(['make', 'distclean'])
        os.chdir(old_path)


'''
Ancient code:


run_arguments = {
    "01_A_program_options_base": "--apples=10 --oranges=20",
    "gil": "get-boost.png",
}

tasks_processor_signals_helper() {                           
    sleep 2;                                                 
    killall tasks_processor_signals -SIGINT; sleep 1;        
    killall tasks_processor_signals -SIGINT; sleep 1;        
    killall tasks_processor_signals -SIGINT; sleep 1;        
}                                                            
interprocess_basics_run() {                                  
    echo "0" | ./Chapter11/interprocess_basics/interprocess_basics
}                                                            
                                                             
chmod -x ./Chapter10/my_library/*                            
for i in `find ./Chapter* -type f -executable`; do           
    echo -e "\n************* Running $i"                     
    progname="$(basename $i)"                                
    case "${progname}" in                                    
    "tasks_processor_signals")                               
        tasks_processor_signals_helper &                     
        ;;                                                   
    "reading_files")                                         
        $i c; time $i m; time $i r; time $i a; continue      
        ;;                                                   
    "interprocess_basics")                                   
        mkfifo fifo1; $i<fifo1 &                             
        sleep 1                                              
        interprocess_basics_run &                            
        interprocess_basics_run &                            
        interprocess_basics_run &                            
        interprocess_basics_run &                            
        interprocess_basics_run &                            
        sleep 1                                              
        echo "0">fifo1                                       
        rm fifo1; continue                                   
        ;;                                                   
    "interprocess_queue")                                    
        $i &                                                 
        ;;                                                   
    "interprocess_pointers")                                 
        $i                                                   
        ;;                                                   
    "regex_match" | "regex_replace")                         
        continue                                             
        ;;                                                   
    "gil")                                                   
        wget http://www.boost.org/style-v2/css_0/get-boost.png
        ;;                                                   
    "01_B_program_options_short")                            
        cp Chapter01/01_B_program_options_short/apples_oranges.cfg ./
        ;;                                                   
    esac                                                     
                                                             
    ./"$i" ${run_arguments["${progname}"]}                      
    if [ $? -ne 0 ] ; then echo "!!! FAILED !!!"; exit -1; fi
done

'''
