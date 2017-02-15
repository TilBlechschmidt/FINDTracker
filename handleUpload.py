# from subprocess import call
import subprocess

Import("env")

def before_spiffs(source, target, env):
    print("Running webpack...")
    p = subprocess.Popen('cd http && ./buildProduction.sh', shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    for line in p.stdout.readlines():
        print line,
    retval = p.wait()

env.AddPreAction("$BUILD_DIR/spiffs.bin", before_spiffs)
