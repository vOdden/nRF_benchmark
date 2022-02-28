import serial, binascii

port = 'COM3'
#binfile = 'C:\\MasterThesis_Nrf\\Anomaly\\datasets\\dcase01\\normal_id_01_00000000_hist_librosa.bin'
binfile =  "C:\\Users\\sigur\\eembc\\runner\\benchmarks\\ulp-mlperf\\datasets\\ic01\\american_elk_s_000045.bin"

def read_and_print(ser):
    while True:
        line = ser.readline().decode('utf-8')
        if len(line) == 0:
            return
        print(line)

def read_and_print_w_count(ser):
    count = 0
    while True:
   
        line = ser.readline().decode('utf-8')
        if len(line) == 0:
            count += 1
            if count == 5*60:
                return
            continue
        print(line)


def write_cmd_and_print(ser, cmd):
    ser.write(cmd.encode('utf-8'))
    read_and_print(ser)




if __name__ == '__main__':
    ser = serial.Serial(port, 115200, timeout=0.1)
    bin_contents = open(binfile, 'rb').read()
    hex_str = binascii.hexlify(bin_contents).decode('utf-8')

    print(f'Length of binary file: {len(bin_contents)}')
    print(f'Length of hex string: {len(hex_str)}')
    # print(f'{list(map(hex, bin_contents[0:10]))}')
    write_cmd_and_print(ser, 'clear%')
    write_cmd_and_print(ser, 'profile%')
    DATA_LOAD = 1
   
if (DATA_LOAD):
    write_cmd_and_print(ser, f'db load {len(bin_contents)}%')
    string_chunk_size = 76
    for i in range(0, len(hex_str), string_chunk_size):
        write_cmd_and_print(ser, f'db {hex_str[i:i + (string_chunk_size)]}%')
        print(f'Percent done: {((i/len(hex_str))*100):.2f}%')
        
    #write_cmd_and_print(ser, f'db print {hex_str}')
    write_cmd_and_print(ser, 'infer 10 1%')
    
    read_and_print_w_count(ser)
    print(f'Waiting for results:', write_cmd_and_print(ser, 'results%') )
    
    
else :
    write_cmd_and_print(ser,'name%')
    write_cmd_and_print(ser, 'infer 10 1%')
    
    read_and_print_w_count(ser)
    rint(f'Waiting for results:', write_cmd_and_print(ser, 'results%') )
  
    



