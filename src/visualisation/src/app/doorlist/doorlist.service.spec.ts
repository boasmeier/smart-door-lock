import { TestBed } from '@angular/core/testing';

import { DoorlistService } from './doorlist.service';

describe('DoorlistService', () => {
  let service: DoorlistService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(DoorlistService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
