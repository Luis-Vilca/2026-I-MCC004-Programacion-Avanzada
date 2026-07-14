#include <vtkActor.h>
#include <vtkCallbackCommand.h>
#include <vtkCubeSource.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCommand.h>
#include "../types.h"

//cmake . -G "MinGW Makefiles"

//Libera la memoria automaticamente
class RotateCallback : public vtkCommand
{
public:
    static RotateCallback* New()
    {
        return new RotateCallback;
    }

    vtkActor* Actor = nullptr;

    void Execute(vtkObject* caller, UL eventId, void*) override
    {
        auto interactor = static_cast<vtkRenderWindowInteractor*>(caller);
        Actor->RotateY(2.0);
        interactor->GetRenderWindow()->Render();
    }
};

//Pipeline de ejecucion:
//vtkCubeSource -> vtkPolyDataMapper -> vtkActor -> vtkRenderer -> vtkRenderWindow -> vtkRenderWindowInteractor
int main()
{
    //Crear la geometria
    vtkNew<vtkCubeSource> cube;
    cube->SetXLength(1);
    cube->SetYLength(1);
    cube->SetZLength(1);

    //Mapper sirve para enviar la geometría a OpenGL
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(cube->GetOutputPort());//Conexión del mapper con la salida del cubo

    //El actor representa un objeto dentro del mundo 3D
    vtkNew<vtkActor> actor;
    //Recibe el mapper, así conoce la geometría y cómo dibujarla
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(0.2,0.8,1.0); //Color en formato RGB

    //Escena, (puede contener a varios actores)
    vtkNew<vtkRenderer> renderer;
    renderer->AddActor(actor);
    renderer->SetBackground(0.1,0.1,0.2); //Color de fondo

    //Ventana física, solo contiene renderizadores
    vtkNew<vtkRenderWindow> window;
    window->AddRenderer(renderer); //Conecta la ventana con el renderer
    window->SetSize(800,600); //Tamaño de la ventana

    //Interactor administra mouse, teclado, eventos y bucle principal de la aplicación
    vtkNew<vtkRenderWindowInteractor> interactor;
    interactor->SetRenderWindow(window); //Conectar el interactor con la ventana

    //Acciones que responden a eventos
    vtkNew<RotateCallback> callback;
    callback->Actor = actor;

    interactor->AddObserver(vtkCommand::TimerEvent, callback);

    interactor->CreateRepeatingTimer(20);

    window->Render();
    //´P
    interactor->Start();

    return 0;
}