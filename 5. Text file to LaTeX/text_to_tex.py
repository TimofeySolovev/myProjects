import re
import codecs

# ПОДГОТАВЛИВАЮТ ТЕКСТ 

# Вспомогательные

def split_text(f_r):
    '''разбивает текст на слова'''
    
    text = []
    for line in f_r:
        text.append(list(line.split()))
    
    return text


def join_text(f_w, text):
    '''соединяет слова в текст'''
    
    new_text = []
    for elm in text:
        new_text.append(' '.join(elm))
    new_text = '\n'.join(new_text)
    
    return new_text

# Основные

def makes_good_gaps(file_name, new_file_name):
    '''делает одинаковые абзацы'''

    f_r = codecs.open(file_name, "r", encoding='utf-8')
    f_w = codecs.open(new_file_name, "w", encoding='utf-8')

    # делим текст на сроки, кладем в список
    text = []
    for line in f_r:
        text.append(line)

    # убираем пустые строки в начале файла
    while text[0] == "\n":
        text.pop(0)

    # убираем пустые строки в файле
    length = len(text)
    for i in range(1, length):
        if text[i] == "\n" and text[i - 1] == "\n":
            while text[i] == "\n":
                text.pop(i)
                text.append("---")

    # убираем лишнее с конца
    while text[-1] == "---" or text[-1] == "\n":
        text.pop(-1)

    new_text = ''.join(text)
    f_w.write(new_text)

    f_r.close()
    f_w.close()
    
    # конец функции makes_good_gaps


def makes_screens_rows(file_name, new_file_name):
    '''выделяет скришоты в отдельные строки'''

    f_r = codecs.open(file_name, "r", encoding='utf-8')
    f_w = codecs.open(new_file_name, "w", encoding='utf-8')

    # делим текст на слова, кладем в список
    text = split_text(f_r)
    
    for elm in text:
        for i in range(len(elm)):
            # выносим названия скринов в отедльные строки
            if '.jpg' in elm[i]:
                elm[i] = "\n\n" + elm[i] + "\n\n"
            
                # убираем лишние знаки препинания перед, между и после скринов
                if i + 1 < len(elm):
                    if elm[i + 1] == "," or elm[i + 1] == "." or elm[i + 1] == "?":
                        elm.pop(i + 1)
                        elm.append("")
                if i - 2 >= 0:
                    if elm[i - 2] == "," or elm[i - 2] == "." or elm[i - 2] == "?":
                        elm.pop(i - 2)
                        elm.append("")            
    
    # собираем текст
    new_text = join_text(f_w, text)
    f_w.write(new_text)

    f_r.close()
    f_w.close()
    
    # конец функции makes_screens_rows


# ПЕРЕВОДЯТ ТЕКСТ В LATEX

def convetrs_text_latex(file_name, new_file_name):
    '''переводит обычный текст в Latex'''

    f_r = codecs.open(file_name, "r", encoding='utf-8')
    f_w = codecs. open(new_file_name, "w", encoding='utf-8')
    
    # вставки для latex документа
    begin = "\\documentclass{article}\n\\usepackage{graphicx}\n\\usepackage[utf8]{inputenc}\n\\usepackage{amsmath}\n" 
    begin += "\\title{Introduction to numerical analysis}\n"
    begin += "\\usepackage[left=2cm, right=2cm, top=2cm, bottom=2cm, bindingoffset=0cm]{geometry}\n"
    begin += "\n\\begin{document}\n\\maketitle\n\n\n"
    end = "\n\n\\end{document}"
    
    f_w.write(begin)

    for line in f_r:
        # убираем лишние пробелы в начале строк
        while line[0] == " ":
            line = line[1:]
        
        # оборачиваем название скриншота
        if ".jpg" in line:
            line = "\\includegraphics[width=\\textwidth]{" + line[:-1] + "}\\\\\n" 
        f_w.write(line)
    
    f_w.write("\n")
    f_w.write(end)

    f_r.close()
    f_w.close()
    
    # конец функции convetrs_text_latex


# ПЕРЕВОДЯТ МАТЕМАТИЧЕСКИЙ ТЕКСТ В LATEX #

# Вспомогательные

def brackets_after_symbol(formula, sym_index):
    '''ставит {} после определенного символа, если есть ()'''
    
    counter1 = 0 # считает "("
    counter2 = 0 # считает ")"
    part = formula[sym_index + 1:]
    index = 0 # индекс нужного вхождения символа
    
    for i in range(len(part)):
        if part[i] == "(":
            counter1 += 1
            
        if part[i] == ")":
            counter2 += 1
            index = i
            
        if counter1 == counter2:
            break
    
    new_formula = formula[:sym_index + 1] + "{" + part[1:index] + "}" + part[index + 1:]

    return new_formula


def brackets_before_symbol(formula, sym_index):
    '''ставит {} до определенного символа, если есть ()'''
    
    counter1 = 0 # считает ")"
    counter2 = 0 # считает "("
    part = formula[:sym_index]
    index = 0 # индекс нужного вхождения символа

    for i in range(len(part) - 1, -1, -1):
        if part[i] == ")":
            counter1 += 1
            
        if part[i] == "(":
            counter2 += 1
            index = i
            
        if counter1 == counter2:
            break
    
    new_formula = part[:index] + "{" + part[index + 1: len(part) - 1] + "}" + formula[sym_index:]

    return new_formula


def no_brackets_after_symbol(formula, sym_index):
    '''ставит {} после определенного символа, если нет ()'''
    
    symbols = "+-*/=^%"
    part = formula[sym_index + 1:]
    index = 0
    
    for i in range(len(part)):
        if part[i] in symbols or i == len(part) - 1:
            index = i
            break
    
    new_formula = formula[:sym_index + 1] + "{" + part[0:index] + "}" + part[index:]
    
    return new_formula


def no_brackets_before_symbol(formula, sym_index):
    '''ставит {} до определенного символа, если нет ()'''
    
    symbols = "+-*/=^%"
    part = formula[:sym_index]
    
    for i in range(len(part) - 1, -1, -1):
        if part[i] in symbols or i == 0:
            index = i
            break
    
    new_formula = part[:index + 1] + "{" + part[index + 1: len(part)] + "}" + formula[sym_index:]
    
    return new_formula


def get_indexes(lst, elm):
    '''возвращает индексы вхождения элемента в массиве'''

    return [i for i in range(len(lst)) if lst[i] == elm]


def get_indexes_mod2(str, elm):
    '''улучшенная версия предыдущей функции (работает для строк)'''

    return [m.start() + len(elm) - 1 for m in re.finditer(elm, str)]

# Основные

def convetrs_mathtext_latex(file_name, new_file_name):
    '''переводит мат. текст в Latex'''

    f_r = codecs.open(file_name, "r", encoding='utf-8')
    f_w = codecs. open(new_file_name, "w", encoding='utf-8')
    
    numbers = "0123456789"
    symbols = "+-*/=^%<>"
    brackets = "()||[]"
    variables = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", 
                 "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"]
    functions = ["\\sqrt(", "\\arcsin(", "\\arccos(", "\\arctan(", "\\arccot(", "\\sin(", "\\cos(", "\\tan(", "\\cot("]
    
    latins = ['alpha', 'beta', 'gamma', 'delta', 'epsilon', 'zeta', 'eta', 'theta', 'iota', 'kappa', 'lambda', 
              'mu', 'nu', 'xi', 'pi', 'rho', 'sigma', 'tau', 'upsilon', 'phi', 'chi', 'psi', 'omega']
    
    # делим текст на слова, кладем в список
    text = split_text(f_r)
    
    for elm in text:
        if elm == [] or "usepackage" in elm[0] or "includegraphics" in elm[0]:
            continue
            
        for i in range(len(elm)): # начинаем с 6, чтобы не задеть вставки Latex
            
            # если есть число или мат. знак - оборачиваем
            for sym in symbols:
                if sym in elm[i]:
                    if "$" in elm[i]:
                        break
                    elm[i] = "$" + elm[i] + "$"
            
            for num in numbers:
                if num in elm[i]:
                    if "$" in elm[i]:
                        break
                    elm[i] = "$" + elm[i] + "$"
            
            if elm[i] == "&":
                elm[i] = "$\\&$"
            
            # если переменная - оборачиваем
            if elm[i] in variables:
                if "$" in elm[i]:
                    break
                if elm[i] != "a" and elm[i] != "i":
                    elm[i] = "$" + elm[i] + "$"
            
            # если латинская буква
            elif elm[i] in latins:
                if "$" in elm[i]:
                    break
                elm[i] = "$\\" + elm[i] + "$"
            
            # для скобок
            elif elm[i][0] in brackets or elm[i][-1] in brackets:
                if "$" in elm[i]:
                    break
                if elm[i][1] in numbers or elm[i][1] in brackets:
                    elm[i] = "$" + elm[i] + "$"
                elif elm[i][1] in variables:
                    elm[i] = "$" + elm[i] + "$"
            
            # если функция - оборачиваем
            for func in functions:
                if func[2:] in elm[i]:
                    if "$" in elm[i]:
                        elm[i] = elm[i].replace(func[1:], func)
                        break
                    else: 
                        elm[i] = "$" + elm[i] + "$"
                        elm[i] = elm[i].replace(func[1:], func)
                        break
    
    # "портим" название функций (это нам пригодится в дальнейшем, 
    # чтобы названия "tan" и "arctan" были различимы относительно корня "tan")
    for elm in text:
        for i in range(len(elm)):
            if "arcsin" in elm[i]:
                elm[i] = elm[i].replace("arcsin", "arcsn")
            elif "arccos" in elm[i]:
                elm[i] = elm[i].replace("arccos", "arccs")
            elif "arctan" in elm[i]:
                elm[i] = elm[i].replace("arctan", "arctn")
            elif "arccot" in elm[i]:
                elm[i] = elm[i].replace("arccot", "arcct")
    
    
    for elm in text:
        for i in range(len(elm)):
            if "$" in elm[i]:
                # пока соседний элемент тоже содержит $  $ - присоединяем
                if i + 1 < len(elm):
                    while "$" in elm[i + 1]:
                        elm[i] = elm[i][:-1]
                        elm[i] = elm[i] + elm[i + 1][1:]
                        elm.pop(i + 1)
                        elm.append("")
    
    
    # собираем текст
    new_text = join_text(f_w, text)
    f_w.write(new_text)
    
    f_r.close()
    f_w.close()
    
    # конец функции convetrs_mathtext_latex


def makes_good_formulas(file_name, new_file_name):
    '''работает с формулами (операции, функции)'''

    f_r = codecs.open(file_name, "r", encoding='utf-8')
    f_w = codecs. open(new_file_name, "w", encoding='utf-8')
    
    functions = ["sqrt", "arcsn", "arccs", "arctn", "arcct", "sin", "cos", "tan", "cot"]

    # делим текст на слова, кладем в список
    text = split_text(f_r)
    
    for elm in text:
        for i in range(len(elm)):
            if "$" in elm[i]:
                
                for func in functions:
                    if func in elm[i]: # эта часть кода необходима, чтобы поместить фнукцию в дробь (если послее нее следует /)
                        for k in range(elm[i].count(func)):

                            list_of_funcs = get_indexes_mod2(elm[i], func) # список индексов func
                            func_index = list_of_funcs[k]

                            elm[i] = brackets_after_symbol(elm[i], func_index) # преобразуем часть справа от func
                            elm[i] = elm[i].replace("{", "(")
                            elm[i] = elm[i].replace("}", "))")
                        
                        old_str = "\\" + func
                        new_str = "(\\" + func
                        
                        elm[i] = elm[i].replace(old_str, new_str)
                
                # возвращаем корректные названия функций
                if "arcsn" in elm[i]:
                    elm[i] = elm[i].replace("arcsn", "arcsin")
                elif "arccs" in elm[i]:
                    elm[i] = elm[i].replace("arccs", "arccos")
                elif "arctn" in elm[i]:
                    elm[i] = elm[i].replace("arctn", "arctan")
                elif "arcct" in elm[i]:
                    elm[i] = elm[i].replace("arcct", "arccot")
            
                
                if "/" in elm[i]: # если есть деление
                    for k in range(elm[i].count('/')):
                        slash_index = elm[i].index("/")

                        if elm[i][slash_index - 1] == ")" and elm[i][slash_index + 1] == "(":
                            elm[i] = brackets_after_symbol(elm[i], slash_index) # преобразуем часть справа от /
                            elm[i] = brackets_before_symbol(elm[i], slash_index) # преобразуем часть слева от /

                        elif elm[i][slash_index - 1] == ")":
                            elm[i] = brackets_before_symbol(elm[i], slash_index) # преобразуем часть слева от /
                            elm[i] = no_brackets_after_symbol(elm[i], slash_index) # преобразуем часть справа от /

                        elif elm[i][slash_index + 1] == "(":
                            elm[i] = brackets_after_symbol(elm[i], slash_index) # преобразуем часть справа от /
                            elm[i] = no_brackets_before_symbol(elm[i], slash_index) # преобразуем часть слева от /

                        else:
                            elm[i] = no_brackets_after_symbol(elm[i], slash_index) # преобразуем часть справа от /
                            elm[i] = no_brackets_before_symbol(elm[i], slash_index) # преобразуем часть слева от /

                        slash_index = elm[i].index("/") # обновляем позицию /
                        elm[i] = elm[i][:slash_index] + elm[i][slash_index + 1:] # убираем /


                        list_of_brackets = get_indexes(elm[i], "{") # список индексов {
                        bracket_index = list_of_brackets[2 * k]

                        elm[i] = elm[i][:bracket_index] + "\\frac" + elm[i][bracket_index:] # добавляем "\frac"
                

                if "*" in elm[i]: # если есть умножение
                    elm[i] = elm[i].replace("*", "\\times ")
                

                if "^" in elm[i]: # если есть возведение в степень
                    for k in range(elm[i].count('^')):
                        list_of_powers = get_indexes(elm[i], "^") # список индексов ^
                        power_index = list_of_powers[k]

                        if elm[i][power_index + 1] == "(":
                            elm[i] = brackets_after_symbol(elm[i], power_index) # преобразуем часть справа от ^

                        else:
                            elm[i] = no_brackets_after_symbol(elm[i], power_index) # преобразуем часть справа от ^
                

                if "sqrt" in elm[i]:
                    for k in range(elm[i].count('sqrt')):
                        list_of_sqrts = get_indexes_mod2(elm[i], "sqrt") # список индексов sqrt
                        sqrt_index = list_of_sqrts[k]

                        elm[i] = brackets_after_symbol(elm[i], sqrt_index) # преобразуем часть справа от sqrt
    
    
    # собираем текст
    new_text = join_text(f_w, text)
    f_w.write(new_text)
    
    f_r.close()
    f_w.close()
    
    # конец функции makes_good_formulas


# УЛУЧШАЮТ ИТОГОВЫЙ ВАРИАНТ ТЕКСТА

def join_punctuation(file_name, new_file_name):
    '''присоединяет знаки препинания'''

    f_r = codecs.open(file_name, "r", encoding='utf-8')
    f_w = codecs. open(new_file_name, "w", encoding='utf-8')

    punctuation = ".,:;?!"
    
    # делим текст на слова, кладем в список
    text = split_text(f_r)
    
    for elm in text:
        for i in range(len(elm)):
            if elm[i] in punctuation:
                elm[i - 1] = elm[i - 1] + elm[i]
                elm.pop(i)
                elm.append("")

    # собираем текст
    new_text = join_text(f_w, text)
    f_w.write(new_text)

    f_r.close()
    f_w.close()
    
    # конец функции makes_good_gaps


# ЗАПУСК ФУНКЦИЙ

makes_good_gaps("daniil_text_end.txt", "timofey_text1.txt")
makes_screens_rows("timofey_text1.txt", "timofey_text2.txt")
convetrs_text_latex("timofey_text2.txt", "timofey_text3.txt")
convetrs_mathtext_latex("timofey_text3.txt", "timofey_text4.txt")
makes_good_formulas("timofey_text4.txt", "timofey_text5.txt")
join_punctuation("timofey_text5.txt", "timofey_text_end.tex")
