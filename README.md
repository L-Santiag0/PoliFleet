# PoliFleet 🚓

Sistema de gerenciamento de viaturas, bases móveis e veículos à paisana da Polícia Militar.

## 📑 Índice

 - <a href="#-sobre-o-projeto">📚 Sobre o Projeto </a>

 - <a href="#-autores">👨‍💻 Autores</a>

 - <a href="#-funcionalidades">🎯 Funcionalidades</a>

 - <a href="#️-tecnologias-utilizadas">🛠️ Tecnologias Utilizadas</a>

 - <a href="#-em-desenvolvimento">🚧 Em Desenvolvimento</a>

 - <a href="#-licença">📄 Licença</a>

## 📚 Sobre o Projeto

Este projeto foi desenvolvido como atividade avaliativa da disciplina **Lógica de Programação II (LP-II)** na **Universidade Estadual de Santa Cruz (UESC)**, sob orientação do professor **Luciano Angelo Souza Bernades**.

O sistema permite o controle de cadastro, alocação e registro de eventos relacionados aos veículos operacionais da PM, promovendo maior organização, segurança e agilidade no planejamento das operações.

## 👨‍💻 Autores

- Evanderson Silva  
- João Guilherme  
- Lucas Santiago

## 🎯 Funcionalidades

📋 **Gestão da Frota**

- [x] Cadastro Completo: Permite registrar novas viaturas com informações detalhadas, incluindo tipo, placa, RENAVAM, cor, quilometragem e status. 

- [x] Listagem Detalhada: Exibe uma lista de todas as viaturas cadastradas com seus respectivos dados e alertas.  

- [x] Alteração de Dados: Possui duas modalidades de alteração:

    1. Completa: Permite que usuários autorizados (Comando, Manutenção) modifiquem todos os dados de uma viatura.

    2. Básica: Permite a rápida atualização do policial responsável e do turno de operação.

- [x] Exclusão de Viaturas: Remove permanentemente uma viatura do sistema (ação restrita a perfis com permissão). 

👤 **Gestão de Acesso e Permissões**

- [ x ] Sistema de Login: Acesso ao sistema protegido por autenticação de usuário e senha.

- [ x ] Níveis de Permissão: O sistema conta com diferentes perfis de usuário, cada um com acesso a funcionalidades específicas:

    1. Comando: Acesso total a todas as funcionalidades, incluindo criação de novos usuários.

    2. Operador: Acesso focado na consulta e alteração de dados básicos de operação.

    3. Manutenção: Acesso focado no cadastro, alteração e exclusão de viaturas.

- [ x ] Logout Inteligente: Permite a troca de usuário sem a necessidade de reiniciar o programa, mantendo todos os dados da sessão atual.

- [ x ] Criação de Usuários: Funcionalidade restrita ao perfil "Comando" para garantir o controle de acesso.

🔔 **Alertas e Automação**

- [ x ] Alerta de Documentos Vencidos: O sistema verifica automaticamente a data atual e exibe alertas visuais para viaturas com:

    1. IPVA vencido

    2. Licenciamento vencido

    3. Seguro vencido

- [ x ] Alerta de Manutenção Preventiva: Notifica o usuário quando uma viatura ultrapassa 10.000 km desde a última revisão registrada, auxiliando no controle da manutenção da frota.

🔍 **Busca e Filtros**

- [ x ] Mecanismo de Busca Rápida: Permite localizar viaturas na base de dados através de diferentes critérios:

    1. Por Placa do veículo.

    2. Por Turno de operação (manhã, tarde, noite).

    3. Por Nome do Policial responsável.

🛡️ **Segurança e Rastreabilidade**

- [ x ] Log de Atividades: Todas as ações críticas (login, logout, cadastro, alteração e exclusão) são registradas em um arquivo de texto (log_acessos.txt). Cada registro contém data, hora, usuário e a ação realizada, garantindo total rastreabilidade.

- [ x ] Modo Disfarçado (Viaturas Paisanas): Para proteger informações sensíveis, os dados de viaturas cadastradas como "paisana" são exibidos de forma restrita para usuários sem permissão elevada, mostrando apenas o status e o responsável.

## 🛠️ Tecnologias Utilizadas

- Linguagem: C 
 
- Ferramentas: Git, GitHub, Visual Studio Code (VS Code), Code::Blocks.


## 🚧 Em Desenvolvimento

Este projeto está em andamento. Funcionalidades adicionais e melhorias serão implementadas nas próximas versões.

## 📄 Licença

Projeto desenvolvido para fins acadêmicos. Uso livre com créditos aos autores.