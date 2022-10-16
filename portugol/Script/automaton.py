import xml.etree.ElementTree as et
import re
import sys

FIRST_ID_STATE = None
XML_PATH = sys.argv[1]

def expand_re(regex):
   expansion = []
   for i in range(0, 127):
        if(re.match(regex, chr(i))):
            expansion.append(i)

   return expansion
ID_TRANSITION = expand_re('[a-zA-Z0-9_]')

# parse XML file into ElementTree object 
def parse_xml(filename):
    tree = et.parse(filename)
    root = tree.getroot()

    return root

# get all states from XML file
def get_states(root):
    states = [(0, 'ERROR', False)]
    global FIRST_ID_STATE

    for state in root.iter('state'):
        if(state.find('label') is not None):
            label = state.find('label').text
            if(FIRST_ID_STATE is None and label == 'ID'):
                FIRST_ID_STATE = int(state.get('id')) + 1
        else:
            label = 'ERRO'
        states.append((int(state.get('id')) + 1, label,           \
            state.find('final') is not None))

    return states

# get all transitions from XML file
def get_transitions(root, states):
    transitions = []
    for transition in root.iter('transition'):
        from_state = transition.find('from').text

        if(states[int(from_state) + 1][1] == 'ID'):
            for t in ID_TRANSITION:
                transitions.append((int(from_state) + 1,         \
                t, FIRST_ID_STATE))

    for transition in root.iter('transition'):
        from_state = transition.find('from').text
        expanded = expand_re(transition.find('read').text)
        
        for t in expanded:
            transitions.append((int(from_state) + 1, t,           \
            int(transition.find('to').text) + 1))

    return transitions

# get all final states from XML file
def get_final_states(root):
    final_states = []
    for state in root.iter('state'):
        if state.find('final') is not None:
            final_states.append(int(state.get('id')) + 1)

    return final_states

# get all initial states from XML file
def get_initial_state(root):
    for state in root.iter('state'):
        if state.find('initial') is not None:
            return int(state.get('id')) + 1

# get all possible tokens from XML file
def get_tokens(root):
    tokens = []
    for state in root.iter('state'):
        if(state.find('label') is not None and state.find('label').text not in tokens):
            tokens.append(state.find('label').text)

    return tokens
    
def main():
    alphabet_size = 128
    automaton = parse_xml(XML_PATH)

    states = get_states(automaton)
    transitions = get_transitions(automaton, states)
    initial_state = get_initial_state(automaton)
    tokens = get_tokens(automaton)

    matrix = [[0 for x in range(alphabet_size)] \
        for y in range(len(states) + 1)]
    
    for transition in transitions:
        matrix[int(transition[0])][transition[1]] = transition[2]

    if('-h' in sys.argv or '--header' in sys.argv):
        print('#ifndef AUTOMATON_H\n#define AUTOMATON_H\n')

    max_state = 0
    for state in states:
        if (state[0] > max_state):
            max_state = state[0]

    if alphabet_size > max_state:
        digits = len(str(alphabet_size))
    else:
        digits = len(str(max_state))

    print(f'#define STATES {max_state + 1}')
    print(f'#define ALPHABET_SIZE {alphabet_size}')
    print(f'#define INITIAL_STATE {initial_state}')
    print(f'#define ERROR_STATE 0')

    type = 'unsigned char'
    if(len(states) > 255):
        type = 'unsigned short'
    elif(len(states) > 65535):
        type = 'unsigned int'
    elif(len(states) > 4294967295):
        type = 'unsigned long'

    print(f'\ntypedef {type} transition_t;')
    # print('typedef enum tokens token_t;')
    print('typedef enum tokens{', end='\t\n')
    print('\tERRO,')
    for tok in tokens:
        print(f'\t{tok},')
    print('} token_t;')
    print('typedef struct state{\n\tconst char* lexeme;\n\ttoken_t tok;\n\tbool is_final;\n} state_t;\n')

    print(f'transition_t transitions[STATES][ALPHABET_SIZE] = ' + '{')
    print('//' + ' ' * int((digits + 3) / 2) + 'states' + ' ' * int((digits + 2) / 2), end='')

    for i in range(alphabet_size):
        if(i < 32 or i > 126):
            print(f'\{str(i)}'.rjust(digits), end='')
        else:
            print(f'{chr(i)}'.rjust(digits), end='')

        if (i != alphabet_size - 1):
            print('  ', end='')

    print('')
    
    for i in range(len(states) + 1):
        print(f'/* {str(i).rjust(digits)} */\t{{', end='')
        for j in range(alphabet_size):
            print(f'{str(matrix[i][j]).rjust(digits)}', end='')
            if (j != alphabet_size - 1):
                print(', ', end='')

        print('\t}', end='')

        if (i != len(states)):
            print(',')
        else:
            print('\n};\n')
    
    print('state_t states[STATES] = {')
    print('\t{\"ERRO\", ERRO, false},')
    for state in states:
        print(f'\t{{ \"{state[1]}\", {state[1]}, {int(state[2])} }},\t\t// {state[0]}')
    print('};\n')
    
    # print('bool is_final[STATES] = {')
    # for i in range(len(states) + 1):
    #     if (i in final_states):
    #         print('\t1', end='')
    #     else:
    #         print('\t0', end='')

    #     if (i != len(states)):
    #         print(f',\t\t// {i}')
    #     else:
    #         print(f'\t\t// {i}\n}};\n')
    
    # print('char *lexemes[STATES] = {')
    # for state in automaton.iter('state'):
    #     if (state.find('label') is not None):
    #         print('\t\"{}\",\t\t// {}'.format(state.find('label').text, state.get('id')))
    #     else:
    #         print('\t"ERRO",\t\t// {}'.format(state.get('id')))
    # print('};\n')

    if('-h' in sys.argv or '--header' in sys.argv):
        print('#endif', end='')

# create a main function to test the get transitions function
if __name__ == '__main__':
    main()