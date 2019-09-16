import os
import hashlib
Import("env", "projenv")

# access to global construction environment
# print env

# access to project construction environment
# print projenv

# Dump construction environments (for debug purpose)
# print env.Dump()
# print projenv.Dump()

BUILD_NUMBER = os.environ.get('BUILD_NUMBER') or "0"
projenv.Append(CPPDEFINES=[('BUILD_NUMBER', BUILD_NUMBER)])
os.system("/kvpac/tool/makefsdata.exe web") 

# env.Append(ldscript='stm32f103ve.ld')
def before_upload(source, target, env):
    print
    "before_upload"
    # do some actions


def after_upload(source, target, env):
    print
    "after_upload"
    # do some actions


def buildMD5(source, target, env):
    f=str(target[0])
    print(f,type(f))
    fh=open(f, "rb")
    fr=fh.read()
    md5key = hashlib.md5(fr).hexdigest()

    # Store new PLC filename based on md5 key
    f = open("lastbuildPLC.md5", "w", encoding='utf-8')
    f.write(md5key)
    f.close()


env.AddPreAction("upload", before_upload)
env.AddPostAction("upload", after_upload)
env.AddPostAction("$BUILD_DIR/firmware.bin", buildMD5)
