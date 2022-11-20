interface IPartialScore {
  score: number;
  name: string;
}

interface IScore extends IPartialScore {
  photograph: string;
  image: string;
  timestamp: number;
}

const isValidScore = (input: IPartialScore | unknown): input is IPartialScore => !!input && typeof input === "object" && "score" in input && "name" in input

export { IScore, IPartialScore, isValidScore };
