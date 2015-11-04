# Norm checker

import sys
import os
import fnmatch
import re

def nbColumns(line, maxLimit = None):
    count = 0
    i = 0
    for c in line:
        if maxLimit != None and i >= maxLimit:
            return count
        if c == '\t':
            count = count - (count % 8) + 8
        elif c == '\n':
            return count
        else:
            count = count + 1
        i = i + 1
            
    return count

## Line Checks ##

def lineHeader(line, lineNb):
    if lineNb == 1 and line != "/*\n":
        return (False, "incorrect header (should be '/*')")
    elif lineNb >= 2 and lineNb <= 8 and line[0:2] != "**":
        return (False, "incorrect header (should start with '**')")
    elif lineNb == 9 and line != "*/\n":
        return (False, "incorrect header (should be '*/')")
    return (True, '')

def lineMaxColumns(line, lineNb):
    if nbColumns(line) >= 80:
        return (False, 'max columns exceeded (' + str(nbColumns(line)) + ', max. 80)')
    return (True, '')

def lineBOperators(line, lineNb):
    if lineNb < 10:
        return (True, '')
    for match in re.finditer(r"==|&&|[+\-*/|~!<>]?=|\?|:|\+|/|[<>|]{1,2}", line):
        if line[0] == '#':
            continue
        c1 = line[match.start()-1]
        c2 = line[match.end()]
        if (c1 != ' ' and c1 != '\'') or (c2 != ' ' and c2 != '\''):
            if c1 == '-':
                continue
            return (False, "binary operator '" + match.group() + "' has too few spaces")
        
    return (True, '')

def lineUOperators(line, lineNb):
    if lineNb < 10:
        return (True, '')
    return (True, '')

def lineExtraSpaces(line, lineNb):
    if lineNb < 10:
        return (True, '')
    lastWasSpace = False
    for c in line:
        if c == ' ' or c == '\t':
            lastWasSpace = True
        elif c != '\n':
            lastWasSpace = False
    if lastWasSpace:
        return (False, 'line has extra spaces')
    else:
        return (True, '')

def lineInstructions(line, lineNb):
    if lineNb < 10:
        return (True, '')
    for match in re.finditer(r"while|return|if|else", line):
        if line[0] == '#':
            continue
        if line[match.end()] != ' ':
            if match.group() == "else" and match.end() == len(line) - 1:
                continue
            return (False, "instruction '" + match.group() + "' has too few spaces")
        elif match.group() == "return" and line[match.end()+1] != '(' and line[match.end()+1] != ';':
            return (False, "instruction 'return' missing '(' or ';'")
    for match in re.finditer(r"for|switch|goto|do", line):
        if line[0] == '#':
            continue
        else:
            return (False, "instruction '" + match.group() + "' is forbidden")

    return (True, '')

lineChecks = [lineHeader,
              lineMaxColumns,
              lineBOperators,
              lineUOperators,
              lineExtraSpaces,
              lineInstructions]

## Functions ##

def checkFuncPrototype(content, pos, isHeader):
    mlIndex = 0
    mlLine = "\n"
    mt = None
    while mt == None and mlIndex < 5 and pos + mlIndex < len(content):
        mlLine = mlLine[:-1] + (" " if mlIndex > 0 else "") + content[pos + mlIndex].lstrip()
        mt = re.match(r"^((?:(?:struct|union) )?[a-z_]{1}[a-z_0-9]*)(\t+)(\**[a-z_]{1}[a-z_0-9]*)\(([a-z_0-9 ,\[\]*()]+)\)\n$", mlLine)
        mlIndex = mlIndex + 1
    if mt != None:
        dFunc = {'return_type': mt.group(1), 'tabs': nbColumns(content[pos], mt.start(3)), 'name': mt.group(3), 'args': mt.group(4), 'lines': mlIndex}
        return ((True, ''), dFunc)
    else:
        return ((False, 'incorrect function declaration'), {})

def checkVarDeclaration(line):
    mt = re.match(r"^  ((?:(?:struct|union|signed|unsigned|volatile|register|const|static) )*[a-z_]{1}[a-z_0-9]*)(\t+)(\**[a-z_]{1}[a-z_0-9]*(?:\[[a-zA-Z_0-9]+\])?);\n$", line)
    if mt == None:
        return ((False, 'incorrect variable declaration'), {})
    dFunc = {'type': mt.group(1), 'tabs': nbColumns(line, mt.start(3)), 'name': mt.group(3)}
    return ((True, ''), dFunc)

def checkFunctions(content, isHeader):
    i = 9
    fLineCount = 0
    fExpected = ""
    currentF = None
    fCount = 0
    while i < len(content):
        if currentF == None:
            if content[i] != "\n":
                return (False, "missing newline", i)
            else:
                i = i + 1
                if content[i][0] == '#':
                    while i < len(content) and content[i][0] == '#':
                        i = i + 1
                    continue
                else:
                    if content[i] == '\n':
                        return (False, "extra newline instead of function declaration", i)
                    result = checkFuncPrototype(content, i, isHeader)
                    if result[0][0] == False:
                        return (False, result[0][1], i)
                    else:
                        fCount = fCount + 1
                        if fCount > 5:
                            return (False, "function '" + result[1]['name'] + "' exceeding max function count (>5)", i)
                        currentF = result[1]
                        fExpected = "{"
                        i = i + currentF['lines']
        else:
            if fExpected == '*1':
                if content[i] == "\n":
                    fExpected = '*2'
                    fLineCount = fLineCount + 1
                    i = i + 1
                    continue
                result = checkVarDeclaration(content[i])
                if result[0][0] == False:
                    return (False, result[0][1], i)
                elif result[1]['tabs'] != currentF['tabs']:
                    return (False, "variable '" + result[1]['name'] + "' is not aligned with the prototype of '" + currentF['name'] + "'", i)
            elif fExpected == '*2':
                if content[i][:-1] == "}":
                    fLineCount = 0
                    currentF = None
                    i = i + 1
                    continue
                elif content[i][:-1] == "":
                    return (False, "incorrect variable block or extra newline in instruction block of function '" + currentF['name'] + "'", i)
                else:
                    result = checkVarDeclaration(content[i])
                    if result[0][0] == True:
                        return (False, "declaration of variable '" + result[1]['name'] + "' is forbidden in instruction block of function '" + currentF['name'] + "'", i)
            elif content[i][:-1] != fExpected:
                return (False, "expected '" + fExpected + "' in function '" + currentF['name'] + "'", i)
            if fExpected == "{":
                if content[i+1].find("\t") == -1:
                    fExpected = '*2'
                else:
                    fExpected = '*1'
            else:
                fLineCount = fLineCount + 1
                if fLineCount > 25:
                    return (False, "line limit exceeded (>25) in function '" + currentF['name'] + "'", i)
            i = i + 1
    if currentF != None:
        return (False, "function '" + currentF['name'] + "' unfinished while reaching end of file", i - 1)
    return (True, '', 0)
                

## Main ##

def checkFile(filename, isHeader):
    err = 0
    with open(filename) as f:
        content = f.readlines()
        # Function checks
        result = checkFunctions(content, isHeader)
        if result[0] != True:
            print(filename + ': check failed at line ' + str(result[2] + 1))
            print(content[result[2]][:-1])
            print('Error: ' + result[1])
            err = err + 1
        # Line checks
        lineNb = 1
        for line in content:
            for checkFunc in lineChecks:
                result = checkFunc(line, lineNb)
                if result[0] != True:
                    print(filename + ": check failed at line " + str(lineNb))
                    print(line[:-1])
                    print('Error: ' + result[1])
                    err = err + 1
            lineNb = lineNb + 1
    if err == 0:
        print(filename + " -> OK")
    return err

path = "."
if len(sys.argv) >= 2:
    path = sys.argv[1]
print("checking the norm...")
errorCount = 0
for root, dirnames, filenames in os.walk(path):
    for filename in fnmatch.filter(filenames, '*.c'):
        errorCount = errorCount + checkFile(os.path.join(root, filename), False)
print("there is " + str(errorCount) + " norm error(s)")
