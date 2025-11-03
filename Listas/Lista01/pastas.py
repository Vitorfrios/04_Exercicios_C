import os

# Template do arquivo .cbp
cbp_template = '''<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
<CodeBlocks_project_file>
	<FileVersion major="1" minor="6" />
	<Project>
		<Option title="{project_name}" />
		<Option pch_mode="2" />
		<Option compiler="gcc" />
		<Build>
			<Target title="Debug">
				<Option output="bin/Debug/{project_name}" prefix_auto="1" extension_auto="1" />
				<Option object_output="obj/Debug/" />
				<Option type="1" />
				<Option compiler="gcc" />
				<Compiler>
					<Add option="-g" />
				</Compiler>
			</Target>
			<Target title="Release">
				<Option output="bin/Release/{project_name}" prefix_auto="1" extension_auto="1" />
				<Option object_output="obj/Release/" />
				<Option type="1" />
				<Option compiler="gcc" />
				<Compiler>
					<Add option="-O2" />
				</Compiler>
				<Linker>
					<Add option="-s" />
				</Linker>
			</Target>
		</Build>
		<Compiler>
			<Add option="-Wall" />
		</Compiler>
		<Unit filename="main.c">
			<Option compilerVar="CC" />
		</Unit>
		<Extensions>
			<lib_finder disable_auto="1" />
		</Extensions>
	</Project>
</CodeBlocks_project_file>'''

# Template do arquivo main.c
main_c_template = '''#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Hello world!\\n");
    return 0;
}'''

def create_exercise_files():
    # Cria arquivos para ex02 até ex10
    for i in range(1, 11):
        project_name = f"ex{i:02d}"  # Formata com zero à esquerda (ex02, ex03, etc.)
        
        # Cria diretório se não existir
        if not os.path.exists(project_name):
            os.makedirs(project_name)
            print(f"Diretório '{project_name}' criado")
        
        # Cria arquivo .cbp
        cbp_content = cbp_template.format(project_name=project_name)
        cbp_filename = os.path.join(project_name, f"{project_name}.cbp")
        
        with open(cbp_filename, 'w', encoding='utf-8') as cbp_file:
            cbp_file.write(cbp_content)
        print(f"Arquivo '{cbp_filename}' criado")
        
        # Cria arquivo main.c
        main_c_filename = os.path.join(project_name, "main.c")
        
        with open(main_c_filename, 'w', encoding='utf-8') as main_c_file:
            main_c_file.write(main_c_template)
        print(f"Arquivo '{main_c_filename}' criado")
        
        print(f"Projeto {project_name} criado com sucesso!")
        print("-" * 50)

if __name__ == "__main__":
    print("Criando projetos ex02 a ex10...")
    print("=" * 50)
    create_exercise_files()
    print("Todos os projetos foram criados com sucesso!")