# help [<help_modifier_list>] [<keyword>]

import openss
#openss.OSS_Init()

my_modifer = openss.ModifierList("brief")
my_modifer+= "examples"

ret = openss.help(my_modifer,"expAttach")
ret = openss.help(my_modifer)
ret = openss.help("expAttach")
ret = openss.help()

print ret

r_count = len(ret)
for ndx in range(r_count):
        print ret[ndx]
