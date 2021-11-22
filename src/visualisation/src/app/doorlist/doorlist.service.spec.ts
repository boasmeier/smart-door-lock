import { TestBed } from '@angular/core/testing';

import { DoorlockService } from '../doorlock_service/doorlock.service';

describe('DoorlistService', () => {
  let service: DoorlockService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(DoorlockService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
