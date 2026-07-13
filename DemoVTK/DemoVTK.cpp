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
    vtkNew<vtkCubeSource> cube;
    cube->SetXLength(1);
    cube->SetYLength(1);
    cube->SetZLength(1);

    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(cube->GetOutputPort());

    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(0.2,0.8,1.0);

    vtkNew<vtkRenderer> renderer;
    renderer->AddActor(actor);
    renderer->SetBackground(0.1,0.1,0.2);

    vtkNew<vtkRenderWindow> window;
    window->AddRenderer(renderer);
    window->SetSize(800,600);

    vtkNew<vtkRenderWindowInteractor> interactor;
    interactor->SetRenderWindow(window);

    vtkNew<RotateCallback> callback;
    callback->Actor = actor;

    interactor->AddObserver(vtkCommand::TimerEvent, callback);

    interactor->CreateRepeatingTimer(20);

    window->Render();
    interactor->Start();

    return 0;
}