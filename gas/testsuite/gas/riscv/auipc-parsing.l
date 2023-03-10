.*: Assembler messages:
.*: Error: illegal operands `auipc x8,x9'
.*: Error: illegal operands `lui x10,x11'
.*: Error: illegal operands `auipc x12,symbol'
.*: Error: illegal operands `lui x13,symbol'
#...
 *[0-9]+[ 	]+# Accept unary .*
 *[0-9]+[ 	]+\?\?\?\? 17070000[ 	]+auipc	x14,%hi \+symbol
 *[0-9]+[ 	]+\?\?\?\? B7B7CBED[ 	]+lui	x15,%hi -0x12345678
