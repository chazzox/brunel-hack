interface IScore {
  score: number;
  name: string;
}

class Score {
  constructor(public data: IScore) {};
}

export { IScore, Score };
