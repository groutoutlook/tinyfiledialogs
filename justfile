shebang := if os() == 'windows' { 'pwsh.exe' } else { '/usr/bin/env pwsh' }
set shell := ["pwsh", "-c"]
set windows-shell := ["pwsh.exe", "-NoLogo", "-Command"]
set dotenv-load := true
# set dotenv-filename	:= ".env"
# set dotenv-required := true
# INFO: if you want to edit the justfile use js -e.

help:
    @just --list -f "{{home_directory()}}/justfile"

default_arg := 'TODO:'
alias td := todo
todo todo=default_arg:
    rg {{todo}} -g '!justfile' -g "!third_party" 

wt:
    #!{{ shebang }}
    wt -f new-tab -p "Developer PowerShell for VS 2022" -d  {{ invocation_directory() }} --tabColor '#FFFFFF'

# INFO: basic `run` recipe.
alias r := run
default_args := 'args here'
run args=default_args:
    @Write-Host {{default_args}} -ForegroundColor Red
    bin\hello_tfd.exe

alias b := build
build: 
    cd {{invocation_directory()}} ; ninja all

clean: 
    cd {{invocation_directory()}} ; ninja clean


