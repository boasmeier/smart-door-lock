import { ComponentFixture, TestBed } from '@angular/core/testing';

import { DoorlistComponent } from './doorlist.component';

describe('DoorlistComponent', () => {
  let component: DoorlistComponent;
  let fixture: ComponentFixture<DoorlistComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ DoorlistComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(DoorlistComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
