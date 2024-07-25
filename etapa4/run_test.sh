#!/bin/bash

# Diretório de entrada contendo os arquivos
input_dir="inputs"

# Arquivo de saída para os resultados
output_file="resultados.txt"

# Limpa o arquivo de resultados anterior, se existir
> "$output_file"

# Função para executar o teste e verificar o código de saída
run_test() {
  local file=$1
  echo
  echo "$file executando"
  echo
  ./etapa4 "$file"
  local exit_code=$?
  
  if [ $exit_code -eq 4 ]; then
    echo "$file: sucesso" >> "$output_file"
  else
    echo "$file: nao foi sucesso (código de saída: $exit_code)" >> "$output_file"
  fi
}

# Verifica se o diretório de entrada existe
if [ ! -d "$input_dir" ]; then
  echo "Diretório '$input_dir' não encontrado."
  exit 1
fi

# Adiciona todos os arquivos no diretório de entrada à lista de arquivos
files=("$input_dir"/*)

# Executa o teste para cada arquivo
for file in "${files[@]}"; do
  if [ -f "$file" ]; then
    run_test "$file"
  else
    echo "$file: não é um arquivo regular" >> "$output_file"
  fi
done

echo "Resultados escritos em $output_file"
