#include <iostream>
#include <map>
#include <memory>

class IPaciente {
public:
    virtual std::string getId();
    virtual void addMedico(IMedico medico);
    virtual void removerMedico(std::string idMedico);
    virtual std::map<std::string, std::shared_ptr<IMedico>> getMedicos();
    virtual std::string getDiagnostico();
};

class IMedico {
public:
    virtual std::string getId();
    virtual void addPaciente(IPaciente paciente);
    virtual void removerPaciente(std::string idPaciente);
    virtual std::map<std::string, IPaciente> getPacientes();
    virtual std::string getClasse();
};

class Medico : public IMedico{
    std::string sender;
    std::string classe;
    std::map<std::string, IPaciente> pacientes;

public:
    Medico(std::string sender, std::string classe);
    std::string getId();
    void addPaciente(IPaciente paciente);
    void removerPaciente(std::string idPaciente);
    std::map<std::string, IPaciente> getPacientes();
    std::string getClasse();
    std::string toString();
};

class Paciente : public IPaciente {
protected:
    std::string sender;
    std::string diagnostico;
    std::map<std::string, IMedico> medicos;

public:
    Paciente(std::string sender, std::string diagnostico);
    std::string getId();
    void addMedico(IMedico medico);
    void removerMedico(std::string idMedico);
    std::map<std::string, std::shared_ptr<IMedico>> getMedicos();
    std::string getDiagnostico();
    friend std::ostream& operator<<(std::ostream& os, Paciente* paciente);
};

class Hospital {
private:
    std::map<std::string, std::shared_ptr<IPaciente>> pacientes;
    std::map<std::string, std::shared_ptr<IMedico>> medicos;
public:
    Hospital();
    void removerPaciente(std::string sender);
    void removerMedico(std::string sender);
    void addPaciente(IPaciente paciente);
    void addMedico(IMedico medico);
    void vincular(std::string nomeMedico, std::string nomePaciente);
    friend std::ostream& operator<<(std::ostream& os, Hospital* h);
};