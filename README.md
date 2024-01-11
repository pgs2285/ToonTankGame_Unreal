# Unreal_ToonTank

-[개요](#개요)  
-[개발시 알아둘것](#개발-시-알아둘것)  
    -[1. 전방선언](#1-클래스-전방선언)  

## 개요

Unreal 로 제작하는 첫 게임.  
그동안 Unity는 많이 사용해보았지만, Unreal에 관심이생겨 제작해보는 첫 프로젝트이다

## 언리얼 내용

유니티와 달랐던 내용을 위주로 서술한다.

#### 1. 클래스 전방선언

이론적으로는 식별자를 정의하기전 식별자의 존재를 컴파일러에게 미리 알려주는 것으로 컴파일 시간을 단축시켜주고, 헤더포함 의존성을 줄여준다.  

```cpp
    class UCapsuleComponent* comp
```

위와 같은 선언을 전방선언이라 한다. 헤더파일에 다른 헤더파일을 include하게 될시 추후 다른 곳에서 불러올때 쓸대없이 다른 헤더파일을 포함하는 관계가 될 수 있다.  
이를 방지하기 위한것이 전방선언이다. 즉 구현부에는 #include "(사용할 헤더).h"를 할지라도, 선언부에는 전방선언으로 형태만 알려주는것이다.  
**이렇게 된것은 클래스에 대한 정보가 없으니 포인터만 사용해야 한다**  해당 객체 할당 크기를 정확히 파악할 수 없으니, 포인터형으로 선언 시 4바이트(32bit OS에서)를 할당한다.

#### 2. UPROPERTY

![](./githubImage/graph.png)

다만 component 들은 visible로만 해도 수정이 되는것을 볼 수 있는데 그 상황에서

Edit은 포인터 자체를 수정하겠다는 의미가 됩과

반면 Visible은 포인터의 멤버를 노출하겠다는 의미가 된다.

#### 3. 유니티와 비슷한듯 다른 언리얼의 이동법

```cpp
// header에 선언해주고,
//Pawn 클래스 내 SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) 메소드가 있는데
// 이 메소드의 파라미터 값을 통해 Binding 한다
void APawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

  /*
   BindAxis 파라미터
   TEXT("MoveForward") -> Project Setting 내 `입력`에서 설정한 이름 설정
   this -> 바인딩할 오브젝트
   &APawn::MoveForward -> 키 값을 적용할 메소드명(매개변수 로 값이 들어
  */
    PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,&ATESTPawn::MoveForward);
}
```

Input.GetAxis, GetButton 등으로 불러왔던 유니티와는 다르게, 부모에서 상속받아 매개변수로 값을 넘겨받아오는 식이라 조금 신선해 적어뒀다.

#### 대치되는듯한 함수

- 유니티에서의 게임오브젝트를 찾는(FindWith...) ->
  언리얼의  GetPlayerPawn (Kismet/GameplayStatics.h) (player index사용)

- 유니티의 캐스팅 as (예시 : Instantiate(a) **as** GameObject) ->
  언리얼의 캐스팅 Cast<바꿀형태>(바꿀것)(예시 : Cast<A>(B))

- 유니티의 생성 Instantiate ->
  언리얼의 생성 GetWorld() -> SpawnActor()
