import os
import sys
import signal
import subprocess
import re
import shutil

class flattener:
    ''' ****************************************** Private functions ********************************************** '''
    @staticmethod
    def _process_source(out, path):
        with open(path, 'r') as f:
            for line in f:
                m = re.findall(r'#include.*"(.*?)"', line)
                if m:
                    d = os.path.dirname(path)
                    flattener._process_source(out, os.path.join(d, m[0]))
                elif 'BOOK_' not in line:
                    out.write(line)

    @staticmethod
    def _flat_source(path):
        flat_name = os.path.join(
            os.path.dirname(path).replace('../', ''),
            "main.cpp"
        )
        try:
            with open(flat_name, 'w+') as out:
                flattener._process_source(out, path)
                if 'tasks_processor_network_accept' in flat_name:
                    with open('../03_tasks_processor_network_client/client.cpp', 'r') as f:
                        for line in f:
                            m = re.findall(r'#include.*"(.*?)"', line)
                            if not m and 'using namespace' not in line:
                                out.write(line)
        except:
            pass

    @staticmethod
    def _is_source(path):
        return os.path.isfile(path) and '.cpp' in path and 'flat' not in path

    ''' ****************************************** Public functions *********************************************** '''
    @staticmethod
    def make_flat():
        print "\nStarting flattening..."

        for folder, _, files in os.walk('..'):
            if 'flat' in folder:
                continue

            for f in files:
                path = os.path.join(folder, f)
                if flattener._is_source(path):
                    flattener._flat_source(path)

        print "\n*** SUCESS ***"


if __name__ == "__main__":
    flattener.make_flat()


